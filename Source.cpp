#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <wchar.h>


#define Max_length  256
#define Max_SinhVien  15

struct SinhVien    // Trường thông tin cần lưu
{
	wchar_t MSSV[10];
	wchar_t HoTen[100];
	wchar_t Khoa[100];
	int KhoaHoc;
	wchar_t NgaySinh[100];
	wchar_t HinhAnh[100];
	wchar_t MoTa[100];
	wchar_t SoThich1[100];
	wchar_t SoThich2[100];
	wchar_t Email[20];
};

wchar_t *docTungPhan(FILE* src, wchar_t *str, int maxSize)   // Hàm xử lý token
{
	wint_t ch;
	int len;
	if (feof(src))
		return NULL;
	str[0] = 0;
	len = 0;
	do
	{
		ch = fgetwc(src);
		if (ch == '\n' || ch == WEOF || ch == ',')
			break;
		if (len < maxSize)
			str[len] = ch;
		len++;
	} while (1);
	str[len] = 0;
	return str;
}

int DocMotSinhVien(FILE* fp, SinhVien& sv)   // Hàm đọc từng dòng thông tin của một sinh viên
{
	docTungPhan(fp, sv.MSSV, 7);

	docTungPhan(fp, sv.HoTen, 30);

	docTungPhan(fp, sv.Khoa, 30);

	fwscanf_s(fp, L"%d", &sv.KhoaHoc);
	wint_t ch = fgetwc(fp);

	docTungPhan(fp, sv.NgaySinh, 10);

	docTungPhan(fp, sv.HinhAnh, 50);

	docTungPhan(fp, sv.MoTa, 50);

	docTungPhan(fp, sv.SoThich1, 50);

	docTungPhan(fp, sv.SoThich2, 50);

	docTungPhan(fp, sv.Email, 20);


	return 1;
}

void DanhSachSinhVien(FILE* fp, SinhVien ds[], int &n)    // Đọc thông tin sinh viên từ file vào trường từ đó suy ra số lượng sinh viên
{
	SinhVien sv;
	n = 0;
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

void docFileHtm(FILE* fp, wchar_t*&str)     // Đọc thông tin file vào một chuỗi
{
	wchar_t ch;
	int i = 0;
	while (!feof(fp))
	{
		ch = fgetwc(fp);
		str = (wchar_t*)realloc(str, (i + 1) * sizeof(wchar_t));
		str[i] = ch;
		i++;
	}
}

int FindSubString(wchar_t* str, wchar_t* substr, int startPos)   // Tìm chuỗi cha trong chuỗi con từ vị trí cho trước
{
	int length = wcslen(str);
	int length1 = wcslen(substr);
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

void DeleteSubString(wchar_t* src, int startPos, int numwchar_t)  // Xóa số kí tự trong chuỗi từ một vị trí
{
	int length = wcslen(src);
	for (int i = startPos; i < length - numwchar_t; i++)
	{
		src[i] = src[i + numwchar_t];
	}
	src[length - numwchar_t] = '\0';
}

void InsertSubString(wchar_t* str, wchar_t* substr, int startPos) // Chèn chuỗi vào vị trí xác định cho trước
{
	int length = wcslen(str);
	int sublength = wcslen(substr);
	if (startPos > length)
		startPos = length;
	if (startPos < length)
	{
		wchar_t* temp = NULL;
		temp = (wchar_t*)malloc((length - startPos + 1) * sizeof(wchar_t));
		wcscpy(temp, str + startPos);
		wcscpy(str + startPos, substr);
		wcscpy(str + startPos + sublength, temp);
	}
	else
	{
		wcscpy(str + startPos, substr);
	}

}

int CountMatches(wchar_t* str, wchar_t *substr)   // Đếm sự xuất hiện của chuỗi cha trong chuỗi con
{
	int length1 = wcslen(str);
	int length2 = wcslen(substr);
	wchar_t* strnew = (wchar_t*)malloc(length2*sizeof(wchar_t));
	int count = 0;
	for (int i = 0; i < length1; i++)
	{
		strnew = &str[i];
		int flag = 0;
		for (int j = 0; j < length2; j++)
		{
			if (strnew[j] != substr[j])
				flag = 1;
		}
		if (flag == 0)
			count++;
	}
	return count;
}
void TimKiemVaThayThe(wchar_t *s, wchar_t *s1, wchar_t *s2)
{

	int n1 = wcslen(s1);
	int pos = FindSubString(s, s1, 0);   // Tìm vị trí giống đầu tiên
	int x, i = 0;
	int count = CountMatches(s, s1);    // Đếm số lần xuất hiện
	while (i<count)
	{
		DeleteSubString(s, pos, n1);
		InsertSubString(s, s2, pos);
		x = FindSubString(s, s1, pos);
		pos = x;
		i++;
	}
}

void XuatFileHtm(SinhVien x, wchar_t* s)
{
	wchar_t filename[30];
	wcscpy(filename, x.MSSV);                     // Tạo file MSSV.htm 
	wcscat(filename, L".htm");
	FILE*fp = _wfopen(filename, L"wt,ccs=UTF-8");

	wchar_t* s1 = wcsdup(s);

	TimKiemVaThayThe(s1, L"Nguyễn Văn A", x.HoTen);
	TimKiemVaThayThe(s1, L"NGUYỄN VĂN A", x.HoTen);
	TimKiemVaThayThe(s1, L"1212123", x.MSSV);
	TimKiemVaThayThe(s1, L"Công nghệ thông tin", x.Khoa);
	TimKiemVaThayThe(s1, L"nva@gmail.com", x.Email);
	TimKiemVaThayThe(s1, L"20/01/1994", x.NgaySinh);                // Thay thế các thông tin từ chuỗi gốc
	TimKiemVaThayThe(s1, L"Âm nhạc: POP, Balad", x.SoThich1);
	TimKiemVaThayThe(s1, L"Ẩm thực: bún riêu, bún thịt nướng", x.SoThich2);
	TimKiemVaThayThe(s1, L"Tôi là một người rất thân thiện.", x.MoTa);
	TimKiemVaThayThe(s1, L"HinhCaNhan.jpg", x.HinhAnh);
	TimKiemVaThayThe(s1, L"KHOA CÔNG NGHỆ THÔNG TIN", x.Khoa);
	TimKiemVaThayThe(s1, L"MSSV ", L"1712882");
	TimKiemVaThayThe(s1, L"Tên sinh viên thực hiện", L"Nguyễn Thanh Tùng");

	fputws(s1, fp);
	fclose(fp);
}


void wmain()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	int n;
	SinhVien ds[Max_SinhVien];
	FILE* src = _wfopen(L"myfile.csv", L"rt,ccs=UTF-8");
	if (src == NULL)
	{
		printf("File khong ton tai");
		return;
	}
	DanhSachSinhVien(src, ds, n);

	FILE* htm = _wfopen(L"1212123.htm", L"rt,ccs=UTF-8");
	if (htm == NULL)
	{
		wprintf(L"File khong ton tai");
		return;
	}


	wchar_t*s = NULL;
	docFileHtm(htm, s);

	for (int i = 0; i<n; i++)      // Xuất tất cả file htm sinh viên
		XuatFileHtm(ds[i], s);

	wprintf(L"Số sinh viên trong danh sách : %d\n", n);

	fclose(htm);
	fclose(src);

}