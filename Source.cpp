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
	char SoThich[100];
	char Email[20];
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
		if (ch == '\n' || ch == EOF || ch == ',')
			break;
		if (len < maxSize)
			str[len] = ch;
		len++;
	} while (1);
	str[len] = 0;
	return str;
}

int DocMotSinhVien(FILE* fp, SinhVien& sv)
{
	char ch;
	docTungPhan(fp, sv.MSSV, 7);

	docTungPhan(fp, sv.HoTen, 30);

	docTungPhan(fp, sv.Khoa, 30);

	fscanf_s(fp, "%d", &sv.KhoaHoc);
	ch = fgetc(fp);

	docTungPhan(fp, sv.NgaySinh, 10);

	docTungPhan(fp, sv.HinhAnh, 50);

	docTungPhan(fp, sv.MoTa, 50);

	docTungPhan(fp, sv.SoThich, 50);

	docTungPhan(fp, sv.Email, 20);


	return 1;
}

void DanhSachHocSinh(FILE* fp, SinhVien ds[], int &n)
{
	SinhVien sv;
	n = 0;
	fseek(fp, 3, 1);
	while (!feof(fp))
	{
		if (DocMotSinhVien(fp, sv))
		{
			ds[n++] = sv;
		}
		else
			break;
	}
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
	int pos;
	pos = FindSubString(s, s1, 0);
	DeleteSubString(s, pos, n1);
	InsertSubString(s, s2, pos);
}

void XuatFileHtm(SinhVien x, char *s)
{
	TimKiemVaThayThe(s, "Nguyen Van A", x.HoTen);
	TimKiemVaThayThe(s, "NGUYEN VAN A", x.HoTen);
	TimKiemVaThayThe(s, "Nguyen Van A", x.HoTen);
	TimKiemVaThayThe(s, "1212123", x.MSSV);
	TimKiemVaThayThe(s, "Cong nghe thong tin", x.Khoa);
	TimKiemVaThayThe(s, "nva@gmail.com", x.Email);
	TimKiemVaThayThe(s, "20/01/1994", x.NgaySinh);
	TimKiemVaThayThe(s, "Am nhac: POP, Balad", x.SoThich);
	TimKiemVaThayThe(s, "1212123", x.MSSV);
	TimKiemVaThayThe(s, "Toi la mot nguoi rat than thien.", x.MoTa);
	TimKiemVaThayThe(s, "Images/HinhCaNhan.jpg", x.HinhAnh);
	TimKiemVaThayThe(s, "KHOA CONG NGHE THONG TIN", x.Khoa);
	TimKiemVaThayThe(s, "Ten sinh vien thuc hien", "Nguyen Thanh Tung");
	TimKiemVaThayThe(s, "nva@gmail.com", x.Email);

	char filename[30];
	strcpy(filename, x.MSSV);
	strcat(filename, ".htm");
	FILE*fp = fopen(filename, "w");
	fputs(s, fp);
	fclose(fp);
}

void XuatAllFileHtm(FILE* fp, SinhVien ds[], int n)
{
	for (int i = 0; i < n; i++)
	{
		char *s = (char*)malloc(6000 * sizeof(char));
		docFileHtm(fp, s);
		XuatFileHtm(ds[i], s);
		free(s);
		rewind(fp);
	}
}

void main()
{
	int n;
	SinhVien ds[Max_SinhVien];
	FILE* src;
	fopen_s(&src, "myfile.csv", "rt");
	if (src == NULL)
	{
		printf("File khong ton tai");
		return;
	}
	DanhSachHocSinh(src, ds, n);


	FILE* htm;
	fopen_s(&htm, "1212123.htm", "rt");
	if (htm == NULL)
	{
		printf("File khong ton tai");
		return;
	}

	XuatAllFileHtm(htm, ds, n);

	fclose(src);
	fclose(htm);
}