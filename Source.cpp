#include<stdio.h>
#include<string>
const int Max_length = 256;
const int Max_SinhVien = 15;

struct SinhVien
{
	char MSSV[10];
	char HoTen[100];
	char Khoa[100];
	int KhoaHoc;
	char NgaySinh[100];
	char HinhAnh[100];
	char MoTa[100];
	char SoThich1[50];
	char SoThich2[50];
	char Email[20];
};

struct TenThayThe
{
	char s1[30];
	char s2[30];
	char s3[30];
	char s4[30];
	char s5[30];
	char s6[30];
	char s7[30];
	char s8[50];
	char s9[100];
	char s10[30];
	char s11[30];
	char s12[30];
	char s13[30];
	char s14[30];
	char s15[30];
};

char *docTungPhan(FILE* src, char *str, int maxSize)
{
	int ch, len;
	if (feof(src))
		return NULL;
	str[0] = 0;
	len = 0;
	do
	{
		ch = fgetc(src);
		if (ch == '\n' || ch == EOF || ch == ';')
			break;
		if (len < maxSize)
			str[len] = ch;
		len++;
	} while (1);
	str[len] = 0;
	return str;
}
void DocMotSinhVien(FILE* fp, SinhVien& sv)
{
	char ch;
	docTungPhan(fp, sv.MSSV, 10);

	docTungPhan(fp, sv.HoTen, 30);

	docTungPhan(fp, sv.Khoa, 30);

	fscanf_s(fp, "%d", &sv.KhoaHoc);
	fgetc(fp);

	docTungPhan(fp, sv.NgaySinh, 10);

	docTungPhan(fp, sv.HinhAnh, 50);

	docTungPhan(fp, sv.MoTa, 100);

	docTungPhan(fp, sv.SoThich1, 50);

	docTungPhan(fp, sv.SoThich2, 50);


	docTungPhan(fp, sv.Email, 20);

}



void DanhSachHocSinh(FILE* fp, SinhVien ds[], int n, TenThayThe& t)
{
	SinhVien sv;
	int i = 0;
	fseek(fp, 3, 1);
	while (i<n)
	{
		DocMotSinhVien(fp, sv);
		ds[i] = sv;
		i++;
	}
	docTungPhan(fp, t.s1, 50);
	docTungPhan(fp, t.s2, 50);
	docTungPhan(fp, t.s3, 50);
	docTungPhan(fp, t.s4, 50);
	docTungPhan(fp, t.s5, 50);
	docTungPhan(fp, t.s6, 50);
	docTungPhan(fp, t.s7, 50);
	docTungPhan(fp, t.s8, 50);
	docTungPhan(fp, t.s9, 100);
	docTungPhan(fp, t.s10, 50);
	docTungPhan(fp, t.s11, 50);
	docTungPhan(fp, t.s12, 50);
	docTungPhan(fp, t.s13, 50);
	docTungPhan(fp, t.s14, 50);
	docTungPhan(fp, t.s15, 50);
}


char *docFileHtm(FILE* fp, char *str)
{
	int ch, len;
	if (feof(fp))
		return NULL;
	str[0] = 0;
	len = 0;
	do
	{
		ch = fgetc(fp);
		if (ch == EOF)
		{
			break;
		}
		str[len] = ch;
		len++;
	} while (1);
	str[len] = 0;
	return str;
}

int StringLength(char *s)
{
	int i = 0;
	while (*(s + i) != '\0')
	{
		i++;
	}
	return i;
}
int FindSubString(char* str, char* substr, int startPos)
{
	int length = StringLength(str);
	int length1 = StringLength(substr);
	for (int i = startPos; i < length; i++)
	{
		int flag = 0;
		for (int j = 0; j < length1; j++)
		{
			if (str[j + i] != substr[j])
			{
				flag = 1;
			}
		}
		if (flag == 0)
			return i;
	}
	return -1;
}

void DeleteSubString(char* src, int startPos, int numChar)
{
	int length = StringLength(src);
	for (int i = startPos; i < length - numChar; i++)
	{
		src[i] = src[i + numChar];
	}
	src[length - numChar] = '\0';
}

char* StringCopy(char* dest, char* src)
{
	int LengthSrc = strlen(src);
	int i = 0;
	while (i < LengthSrc)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	dest[LengthSrc] = '\0';
	return dest;
}

void InsertSubString(char* str, char* substr, int startPos)
{
	int length = strlen(str);
	int sublength = strlen(substr);
	if (startPos > length)
		startPos = length;
	if (startPos < length)
	{
		char* temp;
		temp = (char*)malloc((length - startPos + 1) * sizeof(char));
		StringCopy(temp, str + startPos);
		StringCopy(str + startPos, substr);
		StringCopy(str + startPos + sublength, temp);
		free(temp);
	}
	else
	{
		StringCopy(str + startPos, substr);
	}
}

void TimKiemVaThayThe(char *s, char *s1, char *s2)
{
	
	int n = strlen(s);
	int n1 = strlen(s1);
	int n2 = strlen(s2);
	if (strcmp(s1, s2) != 0)
	{
		int pos = FindSubString(s, s1, 0);
		while (pos != EOF)
		{
			DeleteSubString(s, pos, n1);
			InsertSubString(s, s2, pos);
			int n = FindSubString(s, s1, pos);
			pos = n;
		}
	}
	else
		return;
}

void XuatFileHtm(SinhVien x, char *s,TenThayThe t)
{
	TimKiemVaThayThe(s, t.s1, x.HoTen);
	TimKiemVaThayThe(s, t.s2, x.HoTen);
	TimKiemVaThayThe(s, t.s3, x.MSSV);
	TimKiemVaThayThe(s, t.s4, x.Khoa);
	TimKiemVaThayThe(s, t.s5, x.Email);
	TimKiemVaThayThe(s, t.s6, x.NgaySinh);
	TimKiemVaThayThe(s, t.s7, x.SoThich1);
	TimKiemVaThayThe(s, t.s8, x.SoThich2);
	TimKiemVaThayThe(s, t.s9, x.MoTa);
	TimKiemVaThayThe(s, t.s10, x.HinhAnh);
	TimKiemVaThayThe(s, t.s11, x.Khoa);
	TimKiemVaThayThe(s, t.s12, t.s13);
	TimKiemVaThayThe(s, t.s14, t.s15);


	char filename[30];
	strcpy(filename, x.MSSV);
	strcat(filename, ".htm");
	FILE*fp = fopen(filename, "w");
	fputs(s, fp);
	fclose(fp);
}

void XuatAllFileHtm(FILE* fp, SinhVien ds[], int n,TenThayThe t)
{
	for (int i = 0; i < n; i++)
	{
		char *s = (char*)malloc(6000 * sizeof(char));
		docFileHtm(fp, s);
		XuatFileHtm(ds[i], s,t);
		free(s);
		rewind(fp);
	}
}

void main()
{
	int n=10;
	SinhVien ds[Max_SinhVien];
	TenThayThe t;
	FILE* src;
	fopen_s(&src, "myfile.csv", "rt");
	if (src == NULL)
	{
		printf("File khong ton tai");
		return;
	}
	DanhSachHocSinh(src, ds, n,t);


	FILE* htm;
	fopen_s(&htm, "1212123.htm", "rt");
	if (htm == NULL)
	{
		printf("File khong ton tai");
		return;
	}

	XuatAllFileHtm(htm, ds, n,t);


	fclose(src);
	fclose(htm);
}