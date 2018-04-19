#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <wchar.h>


const int Max_length = 256;
const int Max_SinhVien = 15;

struct SinhVien
{
	wchar_t MSSV[10];
	wchar_t HoTen[100];
	wchar_t Khoa[100];
	int KhoaHoc;
	wchar_t NgaySinh[100];
	wchar_t HinhAnh[100];
	wchar_t MoTa[100];
	wchar_t SoThich1[50];
	wchar_t SoThich2[50];
	wchar_t Email[20];
};

struct TenThayThe
{
	wchar_t s1[30];
	wchar_t s2[30];
	wchar_t s3[30];
	wchar_t s4[30];
	wchar_t s5[30];
	wchar_t s6[30];
	wchar_t s7[30];
	wchar_t s8[50];
	wchar_t s9[100];
	wchar_t s10[30];
	wchar_t s11[30];
	wchar_t s12[30];
	wchar_t s13[30];
	wchar_t s14[30];
	wchar_t s15[30];
};

wchar_t *docTungPhan(FILE* src, wchar_t *str, int maxSize)
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
	wchar_t ch;
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


wchar_t *docFileHtm(FILE* fp, wchar_t *str)
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

int StringLength(wchar_t *s)
{
	int i = 0;
	while (*(s + i) != '\0')
	{
		i++;
	}
	return i;
}
int FindSubString(wchar_t* str, wchar_t* substr, int startPos)
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

void DeleteSubString(wchar_t* src, int startPos, int numwchar_t)
{
	int length = StringLength(src);
	for (int i = startPos; i < length - numwchar_t; i++)
	{
		src[i] = src[i + numwchar_t];
	}
	src[length - numwchar_t] = '\0';
}

wchar_t* StringCopy(wchar_t* dest, wchar_t* src)
{
	int LengthSrc = StringLength(src);
	int i = 0;
	while (i < LengthSrc)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	dest[LengthSrc] = '\0';
	return dest;
}

void InsertSubString(wchar_t* str, wchar_t* substr, int startPos)
{
	int length = StringLength(str);
	int sublength = StringLength(substr);
	if (startPos > length)
		startPos = length;
	if (startPos < length)
	{
		wchar_t* temp;
		temp = (wchar_t*)malloc((length - startPos + 1) * sizeof(wchar_t));
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

void TimKiemVaThayThe(wchar_t *s, wchar_t *s1, wchar_t *s2)
{

	int n = StringLength(s);
	int n1 = StringLength(s1);
	int n2 = StringLength(s2);
	if (wcscmp(s1, s2) != 0)
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

void XuatFileHtm(SinhVien x, wchar_t *s, TenThayThe t)
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


	wchar_t filename[30];
	wcscpy(filename, x.MSSV);
	wcscat(filename, L".htm");
	FILE*fp = _wfopen(filename, L"w");
	fputws(s, fp);
	fclose(fp);
}

void XuatAllFileHtm(FILE* fp, SinhVien ds[], int n, TenThayThe t)
{
	for (int i = 0; i < n; i++)
	{
		wchar_t *s = (wchar_t*)malloc(6000 * sizeof(wchar_t));
		docFileHtm(fp, s);
		XuatFileHtm(ds[i], s, t);
		free(s);
		rewind(fp);
	}
}

void main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	int n = 10;
	SinhVien ds[Max_SinhVien];
	TenThayThe t;
	FILE* src= _wfopen(L"myfile.csv", L"rt");
	if (src == NULL)
	{
		wprintf(L"File khong ton tai");
		return;
	}
	DanhSachHocSinh(src, ds, n, t);


	FILE* htm = _wfopen(L"1212123.htm", L"rt");
	if (htm == NULL)
	{
		wprintf(L"File khong ton tai");
		return;
	}

	XuatAllFileHtm(htm, ds, n, t);


	fclose(src);
	fclose(htm);
}