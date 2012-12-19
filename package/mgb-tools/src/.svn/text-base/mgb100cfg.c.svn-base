/*
 *  Read/Write support for MAC/ID/Name settings (3f8000) on MGB100 boards
 *
 *  Copyright (C) 2007 - 2009 Volker Weiss  <dev@tintuc.de>
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
#include <string.h>
#include <sys/ioctl.h>
#include <mtd/mtd-user.h>


#define MGB100_CFG_MAGIC		0x694c
#define MGB100_LENGTH			0x50
#define SEGMENT_SIZE          0x2000
#define REDBOOT_CFG_OFFSET    0x1000
#define REDBOOT_CFG_MAGIC     "REDBOOT"

/* example, if you want to run a squashed rootfs in flash */
/* console=ttyS0,38400 root=/dev/mtdblock2 rootfstype=squashfs ro */

const char *def_linux_cmd = "console=ttyS0,38400 root=/dev/ram0 rw";

/*
Li Header:
00..03: unknown (probably some version number)
04..07: always ffff ffff
08..0b: length payload
0c..0d: checksum of payload
0e..0f: 'Li'
*/

/*
settings block at 3f8000:
00..0f: Li Header
10..15: MAC ID of WLAN Iface, eth is +1
20..2d: product ID
30..??: product name
40..4f: ?
*/

#define MAC_SIZE          6
#define ID_SIZE          16
#define NAME_SIZE        10
#define LINUXCMD_SIZE   256

static unsigned char mac[MAC_SIZE];
static char id[ID_SIZE];
static char name[NAME_SIZE];
static char linuxcmd[LINUXCMD_SIZE];
static unsigned char copyinitrd;
static unsigned char bootwaitcmd;


#define COPY_SHORT(d, o, v)  d[o+0] = (unsigned char)((v) & 0xff); \
                             d[o+1] = (unsigned char)(((v) >> 8) & 0xff)
#define COPY_LONG(d, o, v)   d[o+0] = (unsigned char)((v) & 0xff); \
                             d[o+1] = (unsigned char)(((v) >> 8) & 0xff); \
                             d[o+2] = (unsigned char)(((v) >> 16) & 0xff); \
                             d[o+3] = (unsigned char)(((v) >> 24) & 0xff)

#define READ_SHORT(d, o)     ((unsigned short)(d[o+0]) + \
                             (((unsigned short)(d[o+1])) << 8))
#define READ_LONG(d, o)      ((unsigned long)(d[o+0]) + \
                             (((unsigned long)(d[o+1])) << 8) + \
                             (((unsigned long)(d[o+2])) << 16) + \
                             (((unsigned long)(d[o+3])) << 24))

static unsigned short checksum(unsigned char *data, long size)
{
	long n;
	unsigned short d, cs = 0;
	for (n = 0; n < size; n += 2) {
		d = READ_SHORT(data, n);
		cs += d;
		if (cs < d)
			cs++;
	}
	if (size & 1) {
		d = data[n];
		cs += d;
		if (cs < d)
			cs++;
	}
	return cs;
}

static void init_data(void)
{
	memset(mac, 0, MAC_SIZE);
	memset(id, 0, ID_SIZE);
	memset(name, 0, NAME_SIZE);
}

static int copy_data_from_flash(const unsigned char *p)
{
	unsigned short cs;
	unsigned long size;
	init_data();
	if (0xffffffff != READ_LONG(p, 4))
		return -1;
	if (MGB100_CFG_MAGIC != READ_SHORT(p, 14))
		return -1;
	size = READ_LONG(p, 8);
	if (size < 32 || size > 2048)
		return -1;
/*
	cs = checksum(&p[16], size);
	if (cs != READ_SHORT(p, 12))
		return -1;
*/
	for (cs = 0; cs < MAC_SIZE; cs++)
		mac[cs] = p[cs + 16];
	strncpy(id, (const char *)(&p[32]), ID_SIZE-1);
	strncpy(name, (const char *)(&p[48]), NAME_SIZE-1);
	p += REDBOOT_CFG_OFFSET;
	memset(linuxcmd, 0, LINUXCMD_SIZE);
	strcpy(linuxcmd, def_linux_cmd);
	copyinitrd = 1;
	bootwaitcmd = 255;
	if (strncmp(REDBOOT_CFG_MAGIC, (const char *)(&p[0]),
	            sizeof(REDBOOT_CFG_MAGIC)) == 0) {
		if ((char)(p[32]) != '\xff')
			strncpy(linuxcmd, (const char *)(&p[32]), LINUXCMD_SIZE-1);
		copyinitrd = p[16];
		bootwaitcmd = p[17];
	}
	return 0;
}

static void copy_data_to_flash(unsigned char *p)
{
	unsigned short cs;
	memset(p, 0, MGB100_LENGTH);
	COPY_LONG(p, 4, 0xffffffff);
	COPY_LONG(p, 8, 62);
	COPY_SHORT(p, 14, MGB100_CFG_MAGIC);
	for (cs = 0; cs < MAC_SIZE; cs++)
		p[cs + 16] = mac[cs];
	COPY_SHORT(p, 22, 0x00ff);
	strcpy((char *)(p + 32), id);
	strcpy((char *)(p + 48), name);
	COPY_SHORT(p, 78, 0xffff);
	cs = checksum(p + 16, 62);
	COPY_SHORT(p, 12, cs);
	p += REDBOOT_CFG_OFFSET;
	memset(p, 0, 32 + LINUXCMD_SIZE);
	strcpy(p, REDBOOT_CFG_MAGIC);
	strcpy((char *)(p + 32), linuxcmd);
	p[16] = copyinitrd;
	p[17] = bootwaitcmd;
}

static unsigned char *read_file(const char *name, long size)
{
	FILE *f;
	unsigned char *data = NULL;
	f = fopen(name, "r");
	if (f != NULL) {
		data = (unsigned char *)malloc(size);
		if (data != NULL) {
			if (fread(data, sizeof(char), size, f) != size) {
				free(data);
				data = NULL;
			}
		}
		fclose(f);
	}
	return data;
}

void erase_flash(int fd)
{
	struct erase_info_user ei;
	ei.start = 0;
	ei.length = 0x2000;
	if (ioctl(fd, MEMERASE, &ei) != 0)
		fprintf(stderr, "error erasing flash\n");
}

int write_file(const char *name, unsigned char *data, long size)
{
	FILE *f;
	int fd;
	f = fopen(name, "w");
	if (f == NULL)
		return -1;
	fd = fileno(f);
	if (fd >= 0)
		erase_flash(fd);
	if (fwrite(data, sizeof(char), size, f) != size) {
		fclose(f);
		return -1;
	}
	fclose(f);
	return 0;
}

static void showhelp(void)
{
	puts("usage: mgb100cfg [OPTIONS]");
	puts("");
	puts("         -m0 [<MAC>]      : show/set MAC of wl0");
	puts("         -m1 [<MAC>]      : show/set MAC of eth1");
	puts("         -M0              : show MAC of wl0 (insmod format)");
	puts("         -M1              : show MAC of eth1 (insmod format)");
	puts("         -i [<ID>]        : show/set product ID");
	puts("         -n [<NAME>]      : show/set device name");
	puts("         -l [<LINUX CMD>] : show/set Linux command line (dangerous)");
	puts("         -c [0/1]         : show/set copy mtd2 as initrd (dangerous)");
	puts("         -w [1..255]      : show/set Redboot waittime...");
	puts("         -d <mtd-device>  : MTD device to read/write info from/to");
	puts("");
	exit(1);
}

static void print_mac(unsigned char *mac, unsigned add)
{
	int i;
	for (i = 0; i < MAC_SIZE; i++) {
		unsigned char m;
		char sep;
		if (i != (MAC_SIZE-1)) {
			m = mac[i];
			sep = ':';
		} else {
			m = mac[i] + (add ? 1 : 0);
			sep = '\n';
		}
		printf("%02X%c", m, sep);
	}
}

static void scan_mac(const char *str, unsigned char *mac, unsigned add)
{
	int i;
	unsigned int tmp[6];
	i = sscanf(str, "%2x:%2x:%2x:%2x:%2x:%2x", &tmp[0], &tmp[1], &tmp[2], &tmp[3],
	           &tmp[4], &tmp[5]);
	if (i != 6) {
		fprintf(stderr, "format error (write MAC like this: 03:44:1a:ff:e5:70)\n");
		exit(3);
	}
	for (i = 0; i < 6; i++) {
		mac[i] = (unsigned char)(tmp[i]);
		if (i == 5)
			mac[i] -= (add ? 1 : 0);
	}
}

static void print_mac_module(unsigned char *mac, unsigned add)
{
	int i;
	printf("0x");
	for (i = 3; i >= 0; i--)
		printf("%02X", mac[i]);
	printf(",0x");
	printf("%02X", mac[5] + (add ? 1 : 0));
	printf("%02X", mac[4]);
	printf("\n");
}

int main(int argc, char *argv[])
{
	unsigned char *data;
	char *file = "/dev/mtd4";
	int rc = 0;
	int write = 0;
	int force = 0;
	int i;
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-f") == 0) {
			force = 1;
		}
		if (strcmp(argv[i], "-h") == 0) {
			showhelp();
		}
		if (strcmp(argv[i], "-d") == 0) {
			file = argv[++i];
			break;
		}
	}

	/* init_data(); */
	data = read_file(file, SEGMENT_SIZE);
	if (data != NULL) {
		if (copy_data_from_flash(data) < 0) {
			fprintf(stderr, "invalid data\n");
			rc = 2;
		}
	} else {
		fprintf(stderr, "cannot read file/device\n");
		return 1;
	}

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-m0") == 0) {
			i++;
			if ((i < argc) && argv[i][0] != '-') {
				scan_mac(argv[i], mac, 0);
				write = 1;
			} else {
				i--;
				print_mac(mac, 0);
			}
		}
		if (strcmp(argv[i], "-m1") == 0) {
			i++;
			if ((i < argc) && argv[i][0] != '-') {
				scan_mac(argv[i], mac, 1);
				write = 1;
			} else {
				i--;
				print_mac(mac, 1);
			}
		}
		if (strcmp(argv[i], "-M0") == 0) {
			print_mac_module(mac, 0);
		}
		if (strcmp(argv[i], "-M1") == 0) {
			print_mac_module(mac, 1);
		}
		if (strcmp(argv[i], "-i") == 0) {
			i++;
			if ((i < argc) && argv[i][0] != '-') {
				if (strlen(argv[i]) >= ID_SIZE) {
					fprintf(stderr, "ID too long\n");
					exit(3);
				}
				strcpy(id, argv[i]);
				write = 1;
			} else {
				i--;
				printf("%s\n", id);
			}
		}
		if (strcmp(argv[i], "-n") == 0) {
			i++;
			if ((i < argc) && argv[i][0] != '-') {
				if (strlen(argv[i]) >= NAME_SIZE) {
					fprintf(stderr, "name too long\n");
					exit(3);
				}
				strcpy(name, argv[i]);
				write = 1;
			} else {
				i--;
				printf("%s\n", name);
			}
		}
		if (strcmp(argv[i], "-l") == 0) {
			i++;
			if ((i < argc) && argv[i][0] != '-') {
				if (strlen(argv[i]) >= LINUXCMD_SIZE) {
					fprintf(stderr, "linuxcmd too long\n");
					exit(3);
				}
				strcpy(linuxcmd, argv[i]);
				write = 1;
			} else {
				i--;
				printf("%s\n", linuxcmd);
			}
		}
		if (strcmp(argv[i], "-c") == 0) {
			i++;
			if ((i < argc) && argv[i][0] != '-') {
				copyinitrd = 1;
				if (argv[i][0] == '0')
					copyinitrd = 0;
				write = 1;
			} else {
				i--;
				printf("%s\n", copyinitrd ? "1" : "0");
			}
		}
		if (strcmp(argv[i], "-w") == 0) {
			i++;
			if ((i < argc) && argv[i][0] != '-') {
				bootwaitcmd = (unsigned char)atoi(argv[i]);
				write = 1;
			} else {
				i--;
				printf("%d\n", (int)bootwaitcmd);
			}
		}
	}
	if (write) {
		if (rc != 0 && !force) {
			fprintf(stderr, "unexpected data structure in flash. Did you use the right\n");
			fprintf(stderr, "mtd device? If you are really sure, you can force updating\n");
			fprintf(stderr, "flash memory by using -f switch\n");
			return rc;
		}
		rc = 0;
		copy_data_to_flash(data);
		if (write_file(file, data, SEGMENT_SIZE) != 0) {
			fprintf(stderr, "cannot write to file/flash\n");
			rc = 3;
		}
	}
	return rc;
}
