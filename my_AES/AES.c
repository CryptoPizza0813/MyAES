#include <stdio.h>

const unsigned char SBox[256] = { 
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

unsigned char Xtimes(unsigned char s)
{
	return ((s << 1) ^ ((s >> 7) * 0x1b));

}


void AddRoundKey(unsigned char s[16], unsigned char key[16])
{
	char i = 0;

	for (i = 0; i < 16; i++)
	{
		s[i] = s[i] ^ key[i];
	}
}

void SubBytes(unsigned char s[16])
{
	char i = 0;
	for (i = 0; i < 16; i++)
	{
		s[i] = SBox[s[i]];
	}
}

void Shiftrow(unsigned char s[16])
{
	char i = 0, j = 0;		//for문용
	unsigned char tmp[16] = { 0, };
	for (i = 0; i < 16; i++)
	{
		tmp[i] = s[i];
	}

	s[1] = tmp[5];
	s[5] = tmp[9];
	s[9] = tmp[13];
	s[13] = tmp[1];

	s[2] = tmp[10];
	s[6] = tmp[14];
	s[10] = tmp[2];
	s[14] = tmp[6];

	s[3] = tmp[15];
	s[7] = tmp[3];
	s[11] = tmp[7];
	s[15] = tmp[11];

}

void MixColumn(unsigned char s[16])
{
	//(s<<1) ^ ((s>>7) * 0x1b )
	//(s<<1) ^ ((s>>7) * 0x1b ) ^ state
	char i = 0, j = 0;
	unsigned char tmp[16] = { 0, };
	for (i = 0; i < 16; i++)
	{
		tmp[i] = s[i];
	}

	//printf("%02x\n", (a & 0x7f) << 1);
	//printf("%02x\n", (a & 0x80) >> 7);


	for (i = 0; i < 4; i++)
	{
		s[4*i] = ((tmp[4*i] << 1) ^ ((tmp[4*i] >> 7) * 0x1b)) ^ ((tmp[4*i + 1] << 1) ^ ((tmp[4*i + 1] >> 7) * 0x1b)) ^ tmp[4*i + 1] ^ tmp[4*i + 2] ^ tmp[4*i + 3];
		s[4*i + 1] = tmp[4*i] ^ ((tmp[4*i + 1] << 1) ^ ((tmp[4*i + 1] >> 7) * 0x1b)) ^ ((tmp[4*i + 2] << 1) ^ ((tmp[4*i + 2] >> 7) * 0x1b)) ^ tmp[4*i + 2] ^ tmp[4*i + 3];
		s[4*i + 2] = tmp[4*i] ^ tmp[4*i + 1] ^ ((tmp[4*i + 2] << 1) ^ ((tmp[4*i + 2] >> 7) * 0x1b)) ^ ((tmp[4*i + 3] << 1) ^ ((tmp[4*i + 3] >> 7) * 0x1b)) ^ tmp[4*i + 3];
		s[4*i + 3] = ((tmp[4*i] << 1) ^ ((tmp[4*i] >> 7) * 0x1b)) ^ tmp[4*i] ^ tmp[4*i + 1] ^ tmp[4*i + 2] ^ ((tmp[4*i + 3] << 1) ^ ((tmp[4*i + 3] >> 7) * 0x1b)) ;
		//s[4 * i] = Xtimes(s[4 * i]) ^ ((tmp[4 * i + 1] << 1) ^ ((tmp[4 * i + 1] >> 7) * 0x1b)) ^ tmp[4 * i + 1] ^ tmp[4 * i + 2] ^ tmp[4 * i + 3];
	}
	//Xtimes(s[4*i]) 를 쓰니 정수계열이 아니라서 안된다뜸

	/*
	for (i = 0; i < 4; i++)
	{
		s[4 * i] = XTinv(tmp[4*i], 0) ^ XTinv(tmp[4 * i + 1], 1) ^ XTinv(tmp[4 * i + 2], 2) ^ XTinv(tmp[4 * i + 3], 3);
		s[4 * i + 1] = XTinv(tmp[4 * i], 3) ^ XTinv(tmp[4 * i + 1], 0) ^ XTinv(tmp[4 * i + 2], 1) ^ XTinv(tmp[4 * i + 3], 2);
		s[4 * i + 2] = XTinv(tmp[4 * i], 2) ^ XTinv(tmp[4 * i + 1], 3) ^ XTinv(tmp[4 * i + 2], 0) ^ XTinv(tmp[4 * i + 3], 1);
		s[4 * i + 3] = XTinv(tmp[4 * i], 1) ^ XTinv(tmp[4 * i + 1], 2) ^ XTinv(tmp[4 * i + 2], 3) ^ XTinv(tmp[4 * i + 3], 0);

		//2배  Xtimes(s[4 * i]) ^  4배  Xtimes(Xtimes(s[4 * i])) 8배 Xtimes(Xtimes(Xtimes(s[4 * i])))
		//e = Xtimes(Xtimes(Xtimes(s[4 * i]))) ^ Xtimes(Xtimes(s[4 * i])) ^ Xtimes(s[4 * i])
		//b = Xtimes(Xtimes(Xtimes(s[4 * i]))) ^ Xtimes(s[4 * i]) ^ s[4*i]
		//d = Xtimes(Xtimes(Xtimes(s[4 * i]))) ^ Xtimes(Xtimes(s[4 * i])) ^ s[4*i]
		//9 = Xtimes(Xtimes(Xtimes(s[4 * i]))) ^ s[4*i]
	}
	*/
}

void KeyExpansion(unsigned char key[16], unsigned char RC[10], unsigned char r)
{
	char i = 0, j = 0;
	unsigned char RotWord[4] = {  key[13], key[14], key[15], key[12] };
	for (i = 0; i < 4; i++)
	{
		RotWord[i] = SBox[RotWord[i]];
	}
	RotWord[0] = RotWord[0] ^ RC[r];
	for (i = 0; i < 4; i++)
	{
		key[4*i] = key[4 * i] ^ RotWord[0];
		key[4*i + 1] = key[4 * i + 1] ^ RotWord[1];
		key[4*i + 2] = key[4 * i + 2] ^ RotWord[2];
		key[4*i + 3] = key[4 * i + 3] ^ RotWord[3];

		RotWord[0] = key[4 * i];
		RotWord[1] = key[4 * i + 1];
		RotWord[2] = key[4 * i + 2];
		RotWord[3] = key[4 * i + 3];

	}
}

unsigned char main()
{
	unsigned char state[16] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
	unsigned char key[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
	unsigned char RC[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };
	unsigned char s[16] = { 0, };
	char i = 0, j = 0;
	
	for (i = 0; i < 16; i++)
	{
		s[i] = state[i];
	}


	//AddRoundKey

	AddRoundKey(s, key);

	

	//루프시작
	char r = 0;
	for (r = 0; r < 10; r++)
	{
		printf("\n%d Start of the Round\n", r + 1);
		for (i = 0; i < 4; i++)
		{
			printf("%02x %02x %02x %02x\n", s[i], s[i + 4], s[i + 8], s[i + 12]);
		}
		printf("\n");

		SubBytes(s);
		
		printf("\n%d check SubBytes\n", r + 1);
		for (i = 0; i < 4; i++)
		{
			printf("%02x %02x %02x %02x\n", s[i], s[i + 4], s[i + 8], s[i + 12]);
		}
		printf("\n");

		Shiftrow(s);

		printf("\n%d check ShiftRows\n", r + 1);
		for (i = 0; i < 4; i++)
		{
			printf("%02x %02x %02x %02x\n", s[i], s[i + 4], s[i + 8], s[i + 12]);
		}
		printf("\n");

		if (r != 9)
		{
			MixColumn(s);

			printf("\n%d check MixColumns\n", r + 1);
			for (i = 0; i < 4; i++)
			{
				printf("%02x %02x %02x %02x\n", s[i], s[i + 4], s[i + 8], s[i + 12]);
			}
		}
		KeyExpansion(key, RC, r);

		printf("\n%d check KeyExpansion\n", r + 1);
		for (i = 0; i < 4; i++)
		{
			printf("%02x %02x %02x %02x\n", key[i], key[i + 4], key[i + 8], key[i + 12]);
		}

		AddRoundKey(s, key);

		
		printf("\n----------------------------------------------\n");

	}
	//10라운드 끝

	

	printf("\n%d Ciphertext\n", r + 1);
	for (i = 0; i < 4; i++)
	{
		printf("%02x %02x %02x %02x\n", s[i], s[i + 4], s[i + 8], s[i + 12]);
	}
	printf("\n");

	return 0;



}