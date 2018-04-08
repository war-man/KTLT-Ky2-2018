
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

int DocMotSinhVien(FILE* fp,SinhVien& sv)
{
	char ch;
	docTungPhan(fp, sv.MSSV, 10);
	
	docTungPhan(fp, sv.HoTen, 30);
	
	docTungPhan(fp, sv.Khoa, 30);
	
	fscanf_s(fp, "%d", &sv.KhoaHoc);
	fgetc(fp);
	
	docTungPhan(fp, sv.NgaySinh, 10);
	
	docTungPhan(fp, sv.HinhAnh, 50);
	
	docTungPhan(fp, sv.MoTa, 50);
	
	docTungPhan(fp,sv.SoThich, 50);

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


void XuatDanhSachSinhVien(FILE* fp, SinhVien ds[], int n)
{
	for (int i = 0; i < n; i++)
	{
		fprintf(fp,"%s,%s,%s,%d,%s,%s,%s,%s,%s\n",
			ds[i].MSSV, 
			ds[i].HoTen,
			ds[i].Khoa,
			ds[i].KhoaHoc,
			ds[i].NgaySinh,
			ds[i].HinhAnh,
			ds[i].MoTa,
			ds[i].SoThich,
			ds[i].Email
		);
	}
	
}

char *docDuLieuFile(FILE* src, char *str)
{
	int ch, len;
	if (feof(src))
		return NULL;
	str[0] = 0;
	len = 0;
	do
	{
		ch = fgetc(src);
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


void main()
{
	int n;
	SinhVien ds[Max_SinhVien];
	FILE* src;
	fopen_s(&src,"myfile.csv", "rt");
	if (src == NULL)
	{
		printf("File khong ton tai");
		return;
	}
	FILE* dest;
	fopen_s(&dest, "Destination.csv", "wt");
	
	DanhSachHocSinh(src, ds, n);
	
	XuatDanhSachSinhVien(dest, ds, n);

	FILE* htm;
	fopen_s(&htm, "1212123.htm", "r");
	if (htm == NULL)
	{
		printf("File khong ton tai");
		return;
	}
	FILE* test;
	fopen_s(&test, "1212124.htm", "w");
	char *s=(char*)malloc(6000*sizeof(char));
	docDuLieuFile(htm, s);

	fputs(s, test);

	free(s);
	fclose(src);
	fclose(dest);
	fclose(test);
	fclose(htm);
	
}

