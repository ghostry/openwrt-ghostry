/************************************************************************

getPin.c Get the PIN from time and username, used for NetKeeper0825 

CopyRight(c) 2008 Jevons,Silver,W.K.

This program is free software: you can redistribute it and/or modify 
it under the terms of the GNU General Public License(GPL) as published by 
the Free Software Foundation, either version 3 of the License, or 
(at your option) any later version.
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

These notices must be retained in any copies of any part of this
documentation and/or software.

getPin.c ªÒµ√NetKeeper0825∞Ê±æ∏˘æ› ±º‰º”√‹µƒ”√ªß√˚◊÷∑˚¥Æ 

÷¯◊˜»®À˘”–(C) 2008 Jevons,Silver,W.K.

±æ≥Ã–ÚŒ™◊‘”…»Ìº˛£ªƒ˙ø…“¿æ›◊‘”…»Ìº˛ª˘Ωª·À˘∑¢±ÌµƒGNUÕ®”√π´π≤ ⁄»®ÃıøÓ(GPL)
πÊ∂®£¨æÕ±æ≥Ã–Ú‘ŸŒ™∑¢≤º”Î£ØªÚ–ﬁ∏ƒ£ªŒﬁ¬€ƒ˙“¿æ›µƒ «±æ ⁄»®µƒµ⁄∂˛∞ÊªÚ£®ƒ˙◊‘––
—°‘Òµƒ£©»Œ“ª»’∫Û∑¢––µƒ∞Ê±æ°£

±æ≥Ã–Ú «ª˘”⁄—–æøƒøµƒ∂¯º”“‘∑¢≤º£¨»ª∂¯≤ª∏∫»Œ∫Œµ£±£‘»Œ£ª“‡Œﬁ∂‘   €–‘ªÚÃÿ
∂®ƒøµƒ  ”√–‘À˘Œ™µƒƒ¨ æ–‘µ£±£°£œÍ«È«Î≤Œ’’GNUÕ®”√π´π≤ ⁄»®°£

ƒ˙”¶“— ’µΩ∏ΩÀÊ”⁄±æ≥Ã–ÚµƒGNUÕ®”√π´π≤ ⁄»®µƒ∏±±æ£ª»Áπ˚√ª”–£¨«Î–¥–≈÷¡◊‘”…
»Ìº˛ª˘Ωª·£∫59 Temple Place - Suite 330, Boston, Ma 02111-1307, USA°£ 

”¶”√±æŒƒµµªÚ»Ìº˛»Œ∫Œ≤ø∑÷ ±«Î±£¡Ù±æ◊¢ Õ°£
 
***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include "global.h"
#include "md5.h"
#include "getPIN.h"

//byte userByte[32];
//byte RADIUS[32];


//getPIN input:userName output:PINwithUserName
void getPIN(byte *userName,byte *PIN) {
	
	//var
	int i;//—≠ª∑±‰¡ø
	long timedivbyfive;// ±º‰≥˝“‘ŒÂ 
	time_t timenow;//µ±«∞ ±º‰£¨¥”time()ªÒµ√ 
	byte RADIUS[16];//¥’Œª◊÷∑˚ 
	byte timeByte[4];// ±º‰ div 5 
	byte beforeMD5[32];// ±º‰ div 5+”√ªß√˚+¥’Œª 
	MD5_CTX md5;//MD5Ω·ππÃÂ 
	byte afterMD5[16];//MD5 ‰≥ˆ
	byte MD501H[2]; //MD5«∞¡ΩŒª
	byte MD501[3];
	byte timeHash[4]; // ±º‰div5æ≠π˝µ⁄“ª¥Œ◊™∫Û∫Ûµƒ÷µ
	byte temp[32]; //µ⁄“ª¥Œ◊™ªª ±À˘”√µƒ¡Ÿ ± ˝◊È
	byte PIN27[6]; //PINµƒ2µΩ7Œª£¨”…œµÕ≥ ±º‰◊™ªª
	
	//code
	memcpy(RADIUS, "chongqingradius1", 16);
	timenow = time(NULL);
	timedivbyfive = timenow / 5;
	/*printf("%d\n", timedivbyfive);
	printf("%s\n", RADIUS);
	printf("%s\n", userName);*/
	
	for(i = 0; i < 4; i++)
	{
		timeByte[i] = (byte)(timedivbyfive >> (8 * (3 - i)) & 0xFF);
		//printf("%02x",timeByte[i]);
	}
		//printf("\n");
	for(i = 0; i < 4; i++) 
	{
		beforeMD5[i]= timeByte[i];
	}
	for(i = 4; i < 16; i++) 
	{
		beforeMD5[i] = userName[i-4];
	}
	for(i = 16; i < 32; i++) 
	{
		beforeMD5[i] = RADIUS[i-16];
	}
	
	MD5Init(&md5);
	MD5Update (&md5, beforeMD5, 32);
	MD5Final (afterMD5, &md5);
	
	MD501H[0] = afterMD5[0] >> 4 & 0xF;
	MD501H[1] = afterMD5[0] & 0xF;
	
	sprintf(MD501,"%x%x",MD501H[0],MD501H[1]);
	
	for(i = 0; i < 32; i++) 
	{
		temp[i] = timeByte[(31 - i) / 8] & 1;
		timeByte[(31 - i) / 8] = timeByte[(31 - i) / 8] >> 1;
	}
	
	for (i = 0; i < 4; i++) 
	{
		timeHash[i] = temp[i] * 128 + temp[4 + i] * 64 + temp[8 + i]
			* 32 + temp[12 + i] * 16 + temp[16 + i] * 8 + temp[20 + i]
			* 4 + temp[24 + i] * 2 + temp[28 + i];
	}
	
	//printf("%02x%02x%02x%02x\n",timeHash[0],timeHash[1],timeHash[2],timeHash[3]);
	
	temp[1] = (timeHash[0] & 3) << 4;
	temp[0] = (timeHash[0] >> 2) & 0x3F;
	temp[2] = (timeHash[1] & 0xF) << 2;
	temp[1] = (timeHash[1] >> 4 & 0xF) + temp[1];
	temp[3] = timeHash[2] & 0x3F;
	temp[2] = ((timeHash[2] >> 6) & 0x3) + temp[2];
	temp[5] = (timeHash[3] & 3) << 4;
	temp[4] = (timeHash[3] >> 2) & 0x3F;
	
	//printf("%02x%02x%02x%02x%02x%02x\n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5]);
	
	for (i = 0; i < 6; i++) 
	{
		PIN27[i] = temp[i] + 0x020;
		if(PIN27[i]>=0x40) 
		{
			PIN27[i]++;
		}
		//printf("%c",PIN27[i]);
	}
	//printf("\n");
	
	PIN[0] = '\r';
	PIN[1] = '\n';
	
	memcpy(PIN+2, PIN27, 6);
	
	PIN[8] = MD501[0];
	PIN[9] = MD501[1];
	
	//memcpy(PIN+10, userName, 19);
	memcpy(PIN+10, userName, strlen(userName));
}

/*
int main() {
	byte *userName = "057400000000@ND.XY";
	byte PIN[30] = {0};
	getPIN(userName,PIN);
	printf("%s",PIN);
	getchar();
}*/


