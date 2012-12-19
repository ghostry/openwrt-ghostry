/*
 *  flashamit - flash original firmware upgrades
 *
 *  Copyright (C) 2008, 2009, 2010 Volker Weiss  <dev@tintuc.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <mtd/mtd-user.h>

#define MGB100_CFG_MAGIC      0x694c
#define ID_SIZE               16
#define NAME_SIZE             10


#define COPY_SHORT(d, o, v)  d[o+0] = (unsigned char)((v) & 0xff); \
                             d[o+1] = (unsigned char)(((v) >> 8) & 0xff)
#define COPY_LONG(d, o, v)   d[o+0] = (unsigned char)((v) & 0xff); \
                             d[o+1] = (unsigned char)(((v) >> 8) & 0xff); \
													   d[o+2] = (unsigned char)(((v) >> 16) & 0xff); \
													   d[o+3] = (unsigned char)(((v) >> 24) & 0xff)

#define READ_SHORT(d, o)   ((unsigned short)(unsigned char)(d[o+0]) + \
                           (((unsigned short)(unsigned char)(d[o+1])) << 8))
#define READ_LONG(d, o)    ((unsigned long)(unsigned char)(d[o+0]) + \
                           (((unsigned long)(unsigned char)(d[o+1])) << 8) + \
                           (((unsigned long)(unsigned char)(d[o+2])) << 16) + \
                           (((unsigned long)(unsigned char)(d[o+3])) << 24))


static unsigned short checksum(unsigned char *data, unsigned long size)
{
	unsigned long n;
	unsigned short d, cs = 0;
	for (n = 0; n < size; n += 2)
	{
		d = READ_SHORT(data, n);
		cs += d;
		if (cs < d)
			cs++;
	}
	if (size & 1)
	{
		d = data[n];
		cs += d;
		if (cs < d)
			cs++;
	}
	return cs;
}

unsigned char *read_file(const char *name, long *size)
{
	FILE *f;
	unsigned char *data = NULL;
	*size = 0;
	f = fopen(name, "r");
	if (f != NULL)
	{
		if (fseek(f, 0, SEEK_END) == 0)
		{
	    *size = ftell(f);
			if (*size != -1)
			{
				if (fseek(f, 0, SEEK_SET) == 0)
				{
					data = (unsigned char *)malloc(*size);
					if (data != NULL)
					{
						if (fread(data, sizeof(char), *size, f) != *size)
						{
							free(data);
							data = NULL;
						}
					}
				}
			}
		}
		fclose(f);
	}
	return data;
}

/*
void dump(const char *ptr, unsigned len)
{
	unsigned r, c, o;
	for (r = o = 0; o < len; r++) {
		for (c = 0; c < 16; c++) {
			if (o + c < len)
				printf("%02X ", (unsigned)(unsigned char)(ptr[o+c]));
			else
				printf("   ");
		}
		printf("  ");
		for (c = 0; c < 16; c++) {
			if (o + c < len)
				printf("%c",
						(ptr[o+c] >= ' ' && ptr[o+c] <= '\x7e') ? ptr[o+c] : '.');
			else
				printf(" ");
		}
		o += 16;
		printf("\n");
	}
}
*/

void panic(const char *fmt, ...)
{
// TODO
	fprintf(stderr, fmt);
	exit(1);
}

static void showhelp(void)
{
	panic("usage: flashamit <UPGRADE.BIN> <MTD-DEVICE>\n");
}

void *save_malloc(size_t size)
{
	void *ptr;
	ptr = malloc(size);
	if (ptr == NULL)
		panic("no memory\n");
	return ptr;
}

void *read_flash(int fd, off_t offset, size_t length)
{
	void *ptr;
	if (lseek(fd, offset, SEEK_SET) != (off_t)(-1)) {
		ptr = save_malloc(length);
		if (read(fd, ptr, length) == length)
			return ptr;
		free(ptr);
	}
	return NULL;
}

struct flashinfo {
	region_info_t info;
	struct flashinfo *next;
};

region_info_t *find_region(unsigned long off, struct flashinfo *fi)
{
	unsigned i;
	while (fi != NULL) {
		for (i = 0; i < fi->info.numblocks; i++) {
			if ((fi->info.offset + (unsigned long)i * fi->info.erasesize) == off)
				return &fi->info;
		}
		fi = fi->next;
	}
	return NULL;
}

void flash_erase(int fd, struct flashinfo *fi, unsigned long off,
                 unsigned long len)
{
	region_info_t *ri;
	erase_info_t ei;
	while (len != 0) {
		ri = find_region(off, fi);
		if (ri == NULL)
			panic("this should never happen :-(\n");
		ei.start = off;
		ei.length = ri->erasesize;
		printf("erasing  : %08lX .. %08lX\r", (unsigned long)(ei.start),
		        (unsigned long)(ei.start + ei.length - 1));
		fflush(stdout);
//		if (ioctl(fd, MEMUNLOCK, &ei) != 0)
//			panic("\nerror unlocking flash\n");
		if (ioctl(fd, MEMERASE, &ei) != 0)
			panic("\nerror erasing flash\n");
		off += ri->erasesize;
		len -= ri->erasesize;
	}
	printf("\n");
}

void flash_write(int fd, unsigned long off, unsigned long len,
                 const unsigned char *buf)
{
	unsigned long blen = 2048;
	if (lseek(fd, off, SEEK_SET) == (off_t)-1)
		panic("error setting offset\n");
	while (len != 0) {
		if (blen > len)
			blen = len;
		printf("writing  : %08lX .. %08lX\r", off, off + blen - 1);
		off += blen;
		fflush(stdout);
		if (write(fd, buf, blen) != blen)
			panic("\nerror writing to flash\n");
		buf += blen;
		len -= blen;
	}
	printf("\n");
}

void flash_verify(int fd, unsigned long off, unsigned long len,
                  const unsigned char *buf)
{
	unsigned long blen;
	unsigned char cmp[2048];
	if (lseek(fd, off, SEEK_SET) == (off_t)-1)
		panic("error setting offset\n");
	blen = sizeof(cmp);
	while (len != 0) {
		if (blen > len)
			blen = len;
		printf("verifying: %08lX .. %08lX\r", off, off + blen - 1);
		off += blen;
		if (read(fd, cmp, blen) != blen)
			panic("read error while verifying flash\n");
		if (memcmp(buf, cmp, blen) != 0)
			panic("verify error\n");
		buf += blen;
		len -= blen;
	}
	printf("\n");
}


/*
00..0d ASCII product ID
0e..0f checksum of payload
10..1b ASCII Queen
1c..1f AMIT BIOS: 11e1 6bc7, Recovery Tool: 22e2 6bc7
       Linux: 5dc3 47c8, ramdisk: 5cc3 47c8
                         AMIT FS: 21c3 47c8    VERSION NUMBER??????
20..23 offset in flash aligned to segment boundary
24..27 length in flash aligned to segment boundary
28..2b offset in flash (payload)
2c..2f length (payload)
30..3f always 0
40..47 always 4248 0101 5000 0001 (last maybe .....0501)
48..4b same as 20..23
4c..4d always 0b00
4e..4f inverted checksum of header
*/
struct fileheader {
	char *id;
	unsigned long version;
	unsigned long seg_off;
	unsigned long seg_len;
	unsigned long off;
	unsigned long len;
	unsigned short cs;
};

int read_header(FILE *f, struct fileheader *hdr)
{
	unsigned short cs;
	unsigned char buf[0x50];
	if (fread(buf, sizeof(buf), 1, f) != 1) {
		if (feof(f))
			return 0;
		panic("error reading file header\n");
	}
	hdr->id = save_malloc(15);
	memcpy(hdr->id, buf, 14);
	hdr->id[14] = '\0';
	hdr->cs = READ_SHORT(buf, 0x0e);
	if (buf[0x10] != 'Q' || buf[0x11] != 'u' || buf[0x12] != 'e'
				|| buf[0x13] != 'e' || buf[0x14] != 'n' || buf[0x15] != '\0')
		panic("invalid header (0x10)\n");
	hdr->version = READ_LONG(buf, 0x1c);
	hdr->seg_off = READ_LONG(buf, 0x20);
	hdr->seg_len = READ_LONG(buf, 0x24);
	hdr->off = READ_LONG(buf, 0x28);
	hdr->len = READ_LONG(buf, 0x2c);
	if (hdr->seg_off != READ_LONG(buf, 0x48))
		panic("invalid header (0x48)\n");
	cs = checksum(buf, sizeof(buf));
	cs = ~cs;
	if (cs != 0)
		panic("checksum error in header\n");
	if (hdr->off < hdr->seg_off)
		panic("invalid header (off < seg_off)\n");
	if ((hdr->off + hdr->len) > (hdr->seg_off + hdr->seg_len))
		panic("invalid header (off+len > seg_off+seg_len)\n");
	if (hdr->off < (hdr->seg_off + 16))
		panic("invalid header (hdr->off < hdr->seg_off+16)\n");
//printf("%08lX %08lX %08lX %08lX\n", hdr->seg_off, hdr->seg_len, hdr->off, hdr->len);
	return 1;
}

/*
Li Header:
00..03: unknown (probably some version number)
04..07: always ffff ffff
08..0b: length payload
0c..0d: checksum of payload
0e..0f: 'Li'
*/
void make_li_header(unsigned char *hdr, unsigned char *data,
                    unsigned long len)
{
	COPY_LONG(hdr, 0, 0);
	COPY_LONG(hdr, 4, 0xffffffff);
	COPY_LONG(hdr, 8, len);
	COPY_SHORT(hdr, 12, checksum(data, len));
	COPY_SHORT(hdr, 14, MGB100_CFG_MAGIC);
}

/*
MAC/ID block:
00..0f: Li Header
10..15: MAC ID of WLAN Iface, eth is +1
20..2d: product ID
30..??: product name
40..4f: ?
*/


const char *get_device_id(int fd)
{
	char *ptr = NULL;
	unsigned long size;
	char *id = NULL;
	ptr = read_flash(fd, 0x3f8000, 0x50);
	if (ptr == NULL)
		goto err_ret;
	if (0xffffffff != READ_LONG(ptr, 4))
		goto err_ret;
	if (MGB100_CFG_MAGIC != READ_SHORT(ptr, 14))
		goto err_ret;
	size = READ_LONG(ptr, 8);
	if (size < 32)
		goto err_ret;
	id = save_malloc(ID_SIZE);
	strncpy(id, &ptr[32], ID_SIZE-1);
err_ret:
	free(ptr);
	return id;
}

struct flashinfo *get_flash_info(int fd)
{
	struct flashinfo *next = NULL;
	mtd_info_t mtd;
	region_info_t rgn;
	int i;
	int rgn_count;
	if (ioctl(fd, MEMGETINFO, &mtd) == 0) {
		/* TODO: add. checks */
		if (ioctl(fd, MEMGETREGIONCOUNT, &rgn_count) == 0) {
			if (rgn_count != 0) {
				for (i = 0; i < rgn_count; i++) {
					struct flashinfo *tmp;
					rgn.regionindex = i;
					if (ioctl(fd, MEMGETREGIONINFO, &rgn) != 0)
						panic("cannot determine flash regions\n");
					tmp = save_malloc(sizeof(struct flashinfo));
					tmp->next = next;
					tmp->info = rgn;
					next = tmp;
				}
			} else {	/* create dummy region */
				next = save_malloc(sizeof(struct flashinfo));
				next->info.offset = 0;
				next->info.erasesize = mtd.erasesize;
				next->info.numblocks = mtd.size / mtd.erasesize;
				next->info.regionindex = 0;
				next->next = NULL;
			}
		}
	}
	return next;
}

void read_data(FILE *f, unsigned char *buf, size_t len)
{
	if (fread(buf, sizeof(unsigned char), len, f) != len)
		panic("error reading file\n");
}

void check_file(FILE *f, struct flashinfo *fi, const char *id)
{
	struct fileheader hdr;
	unsigned char *buf;
	unsigned long off;
	unsigned cs;
	region_info_t *ri;
	rewind(f);
	while (read_header(f, &hdr)) {
		if (strcmp(id, hdr.id) != 0) {
			fprintf(stderr, "device ID: %s\nfile ID: %s\n", id, hdr.id);
			panic("firmware ID of device and file differ\n");
		}
		buf = save_malloc(hdr.seg_len);
		memset(buf, '\xff', hdr.seg_len);
		off = hdr.off - hdr.seg_off;
		read_data(f, buf + off, hdr.len);
		cs = checksum(buf + off, hdr.len);
		if (cs != hdr.cs)
			panic("checksum error in file\n");
		free(buf);
		do {
			ri = find_region(hdr.seg_off, fi);
			if (ri != NULL && hdr.seg_len >= ri->erasesize) {
				hdr.seg_len -= ri->erasesize;
				hdr.seg_off += ri->erasesize;
			} else {
				panic("data not aligned to region boundary of flash\n");
			}
		} while (hdr.seg_len != 0);
	}
}

void erase_write_verify(FILE *src, struct flashinfo *fi, int dest)
{
	struct fileheader hdr;
	unsigned char *buf;
	unsigned long off;
	rewind(src);
	while (read_header(src, &hdr)) {
		buf = save_malloc(hdr.seg_len);
		memset(buf, '\xff', hdr.seg_len);
		off = hdr.off - hdr.seg_off;
		read_data(src, buf + off, hdr.len);
		make_li_header(buf + off - 16, buf + off, hdr.len);
		flash_erase(dest, fi, hdr.seg_off, hdr.seg_len);
		flash_write(dest, hdr.seg_off, hdr.seg_len, buf);
		flash_verify(dest, hdr.seg_off, hdr.seg_len, buf);
		free(buf);
	}
}

/*
# cat /proc/mounts 
rootfs / rootfs rw 0 0
/dev/root / ext2 rw 0 0
proc /proc proc rw 0 0
tmpfs /tmp tmpfs rw 0 0
/dev/mtdblock3 /etc jffs2 rw,noatime,nodiratime 0 0
/dev/sda1 /usr ext3 ro 0 0
*/

void check_mounts(void)
{
	/* ugly quick and dirty hack */
	/* TODO: better solution to check, if part of the mtd device we
	         want to write to, is mounted */
	FILE *mnt;
	char str[256];
	char *p;
	mnt = fopen("/proc/mounts", "r");
	if (mnt == NULL)
		panic("cannot get mountpoints\n");
	while(fgets(str, sizeof(str), mnt) != NULL) {
		p = strchr(str, ' ');
		if (p != NULL) {
			*p = '\0';
			if (strncmp(str, "/dev/mtd", 8) == 0) {
				panic("you must umount any flash file systems before upgrading\n");
			}
		}
	}
	fclose(mnt);
}

int main(int argc, char *argv[])
{
	FILE *src;
	int dest;
	const char *file;
	const char *dev;
	struct flashinfo *fi;
	const char *id;
	if (argc != 3)
		showhelp();
	file = argv[1];
	dev = argv[2];
	check_mounts();
	dest = open(dev, O_SYNC | O_RDWR);
	if (dest < 0)
		panic("error opening device\n");
	fi = get_flash_info(dest);
	id = get_device_id(dest);
	if (id == NULL)
		panic("cannot detemine device ID\n");
	printf("device ID is: %s\n", id);
	src = fopen(file, "rb");
	if (src == NULL)
		panic("error open file\n");
	check_file(src, fi, id);
	erase_write_verify(src, fi, dest);
	fclose(src);
	close(dest);
	return 0;
}
