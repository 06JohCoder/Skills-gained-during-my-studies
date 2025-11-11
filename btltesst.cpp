/*
_______________________________________
|   Thành Viên Nhóm  |   Mã Sinh Viên |
|_____________________________________|
|	Nguyen Ðuc Quang |	:2411061767	  |
|									  |
|	Tran Minh Quang	 |	:2411062029   |
|									  |
|	Luong Viet Nhat	 |	:2411061614   |
|									  |
|	Hoàng Gia The	 |	:2411061927   |
|									  |
|	Nguyen Tien Dung |	:2411061649   |
|_____________________________________|
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32    
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
#define MAX 100
 
typedef int Position;
 
// Cau truc mon hoc
typedef struct {
    char tenMon[50];
 
} MonHoc;
 
// Cau truc sinh vien
struct Sinhvien {
    char id[20];
    char name[50];
    char ns[20];
    int tuoi;
    float diem[MAX];  
    int soMon;  
    float gpa;        // Thêm
    char hocLuc[20];  // Thêm
};
 
// Kieu danh sach mang
typedef struct {
    struct Sinhvien A[MAX];
    int Last; 
} List;
 
typedef struct {
    MonHoc A[MAX];
    int count;
} MonHocList; 
 
// =============================== Cac thao tac co ban ===============================
 
Position FIRST(List L) {
    return 1;
}
 
Position END(List L) {
    return L.Last + 1;
}
 
Position NEXT(Position P, List L) {
    if (P < END(L)) return P + 1;
    return END(L);
}
 
Position PREVIOUS(Position P, List L) {
    if (P > FIRST(L)) return P - 1;
    return FIRST(L);
}
 
struct Sinhvien RETRIEVE(Position P, List L) {
    return L.A[P-1];
}
 
Position LOCATE(char id[], List L) {
    for (int i = 0; i < L.Last; i++) {
        if (strcmp(L.A[i].id, id) == 0)
            return i+1;
    }
    return END(L);
}
 
void MAKENULL_LIST(List *L) {
    L->Last = 0;
}
 
int EMPTY_LIST(List L){
    return L.Last == 0;
}
 
void INSERT_LIST(struct Sinhvien x, Position P, List *L) {
    if (L->Last >= MAX) {
        printf("Danh sach day\n");
        return;
    }
    if (P < FIRST(*L) || P > END(*L)) {
        printf("Vi tri khong hop le\n");
        return;
    }
    for (int i = L->Last; i >= P; i--) {
        L->A[i] = L->A[i-1];
    }
 
    L->A[P-1] = x;
    L->Last++;
}
 
void DELETE_LIST(Position P, List *L) {
    if (P < FIRST(*L) || P >= END(*L)) {
        printf("Vi tri khong hop le\n");
        return;
    }
    for (int i = P-1; i < L->Last-1; i++) {
        L->A[i] = L->A[i+1];
    }
    L->Last--;
}
 
 
 
// Xoa sinh vien theo MSV
void DELETE_BY_ID(char id[], List *L) {
    printf("\n+==========================================================================+\n");
    printf("|                      XOA SINH VIEN THEO MSV                              |\n");
    printf("+==========================================================================+\n");

    Position p = LOCATE(id, *L);

    if (p == END(*L)) {
        printf("|    Khong tim thay sinh vien co MSV: %-36s|\n", id);
        printf("+==========================================================================+\n");
        return;
    }

    struct Sinhvien sv = L->A[p - 1];

    char confirm;
    printf("|    Tim thay sinh vien:                                                   |\n");
    printf("|    MSSV      : %-59s|\n", sv.id);
    printf("|    Ho ten    : %-59s|\n", sv.name);
    printf("|    Ngay sinh : %-27sTuoi : %-11d              |\n", sv.ns, sv.tuoi);
    printf("+--------------------------------------------------------------------------+\n");
    printf("     Ban co chac chan muon xoa sinh vien nay khong? (y/n): ");
    scanf(" %c", &confirm);
    printf("+==========================================================================+\n");

    if (confirm != 'y' && confirm != 'Y') {
        printf("|    Da huy thao tac xoa sinh vien.                                        |\n");
        printf("+==========================================================================+\n");
        return;
    }

    for (int i = p - 1; i < L->Last - 1; i++) {
        L->A[i] = L->A[i + 1];
    }
    L->Last--;

    printf("|    Da xoa sinh vien thanh cong                                             |\n");
    printf("+--------------------------------------------------------------------------+\n");
    printf("|    Thong tin sinh vien da xoa:                                             |\n");
    printf("|    MSSV      : %-59s|\n", sv.id);
    printf("|    Ho ten    : %-59s|\n", sv.name);
    printf("|    Ngay sinh : %-27sTuoi : %-11d           |\n", sv.ns, sv.tuoi);
    printf("+==========================================================================+\n");
}


 
// ================== Cac chuc nang mo rong ==================
 
void ChuanHoan(char s[], int size) {
    for (int i = 0; i < size; i++) {
        if (s[i] == '/') {
            if (i == 1) { 
                for (int j = size; j >= 0; j--) {
                    s[j+1] = s[j];
                }
                s[0] = '0';
                size++;
            }
            if (s[i+2] == '/' && i+2 < size) {
                for (int k = size; k >= i+1; k--) {
                    s[k+1] = s[k];
                }
                s[i+1] = '0';
                size++;
            }
        }
    }
}
 
int laNamNhuan(int y) {
    return ( (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0) );
}
 
int soNgayTrongThang(int m, int y) {
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        return 31;
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return 30;
    if (m == 2)
        return laNamNhuan(y) ? 29 : 28;
    return 0; 
}
 
void ChuanHoaTen(char *name) {
    char temp[100];
    int i = 0, j = 0;
    int len = strlen(name);
 
    while (i < len && name[i] == ' ') i++;
    int space = 0; 
    while (i < len) {
        if (name[i] != ' ') {
            if (space && j > 0) {
                temp[j++] = ' '; 
                space = 0;
            }
            temp[j++] = name[i];
        } else {
            space = 1;
        }
        i++;
    }
 
    if (j > 0 && temp[j-1] == ' ') j--;
    temp[j] = '\0';
 
    for (i = 0; i < j; i++) {
        if (temp[i] >= 'A' && temp[i] <= 'Z')
            temp[i] = temp[i] - 'A' + 'a';
    }
 
    int newWord = 1;
    for (i = 0; i < j; i++) {
        if (temp[i] == ' ') {
            newWord = 1;
        } else if (newWord && temp[i] >= 'a' && temp[i] <= 'z') {
            temp[i] = temp[i] - 'a' + 'A';
            newWord = 0;
        } else {
            newWord = 0;
        }
    }
 
    strcpy(name, temp);
}
 
struct Sinhvien nhapSinhVien(List L) {
    struct Sinhvien sv;
    printf("\n+-----------------------------------------+\n");
    printf("|        NHAP THONG TIN SINH VIEN MOI     |\n");
    printf("+-----------------------------------------+\n");
    while (1) {
        printf(">> Nhap MSV: ");
        scanf("%s", sv.id);
        if (LOCATE(sv.id, L) != END(L)) {
            printf("MSSV da ton tai, nhap lai\n");
        } else {
            break;
        }
    }
 
 
    int check;
 
    do {
        check = 1; 
        printf(">> Nhap ho ten: ");
        scanf(" %19[^\n]", sv.name); 
 
        for (int i = 0; i < strlen(sv.name); i++) {
            if (!((sv.name[i] >= 'a' && sv.name[i] <= 'z') || (sv.name[i] >= 'A' && sv.name[i] <= 'Z') || sv.name[i] == ' ')) {
                check = 0; 
                break;
            }
        }
 
        if (check == 0) {
            printf("Ho va ten khong chua so hoac ky tu dac biet : \n");
        } else {
 
             ChuanHoaTen(sv.name);
 
        }
    } while (check == 0); 
 
 do {
    printf(">> Nhap ngay sinh (dd/mm/yyyy): ");
    scanf("%s", sv.ns);
 
    int size = strlen(sv.ns);
    ChuanHoan(sv.ns, size);
 
    char day[3], month[3], year[5];
    day[0] = sv.ns[0];
    day[1] = sv.ns[1];
    day[2] = '\0';
    month[0] = sv.ns[3];
    month[1] = sv.ns[4];
    month[2] = '\0';
    
    int index = 6;  
    for (int i = 0; i < 1; i++) {     
        for (int j = 0; j < 4; j++) {  
            year[j] = sv.ns[index + j];
        }
    }
    year[4] = '\0'; 
 
    
    int d = atoi(day);
    int m = atoi(month);
    int y = atoi(year);
    
 
    int maxday = soNgayTrongThang(m,y);
    if (d <= 0 || d > maxday || m <= 0 || m > 12 || y <= 100) {
        printf("Ngay sinh khong hop le vui long nhap lai!\n");
    } else {
        int namNow = 2025;
        do {
            printf(">> Nhap tuoi: ");
            scanf("%d", &sv.tuoi);
            if (sv.tuoi < namNow - y - 2 || sv.tuoi > namNow - y + 2) {
                printf("Vui long nhap lai tuoi dung voi tuoi that cua ban\n");
            }
        } while (sv.tuoi < namNow - y - 2 || sv.tuoi > namNow - y + 2);
        break; 
    }
} while (1);
 
    sv.soMon = 0; 
    sv.gpa = 0.0;
    strcpy(sv.hocLuc, "Chua xep loai");
 
    return sv;
}
 
void PRINT_LIST(List L) {
    if (L.Last == 0) {
        printf("Danh sach rong!\n");
        return;
    }
 
    printf("\n+-----+--------------+---------------------------+--------------+-------+\n");
    printf("| STT | MSSV         | Ho Ten                    | Ngay Sinh    | Tuoi  |\n");
    printf("+-----+--------------+---------------------------+--------------+-------+\n");
 
    for (int i = 0; i < L.Last; i++) {
        printf("| %-3d | %-12s | %-25s | %-12s | %-5d |\n",
               i+1, L.A[i].id, L.A[i].name, L.A[i].ns, L.A[i].tuoi);
    }
 
    printf("+-----+--------------+---------------------------+--------------+-------+\n");
}
 
void SORT_BY_NAME(List *L) {
    for (int i = 0; i < L->Last - 1; i++) {
        for (int j = i + 1; j < L->Last; j++) {
            if (strcmp(L->A[i].name, L->A[j].name) > 0) {
                struct Sinhvien tmp = L->A[i];
                L->A[i] = L->A[j];
                L->A[j] = tmp;
            }
        }
    }
    printf("Da sap xep theo ten\n");
}
 
void SORT_BY_TUOI(List *L) {
    for (int i = 0; i < L->Last - 1; i++) {
        for (int j = i + 1; j < L->Last; j++) {
            if (L->A[i].tuoi > L->A[j].tuoi) {
                struct Sinhvien tmp = L->A[i];
                L->A[i] = L->A[j];
                L->A[j] = tmp;
            }
        }
    }
    printf("Da sap xep theo tuoi\n");
}

void themMonHoc(MonHocList *dsMon) {
    if (dsMon->count >= MAX) {
        printf("Danh sach mon hoc da day!\n");
        return;
    }

    MonHoc mh;
    printf(">> Nhap ten mon hoc: ");
    scanf(" %[^\n]", mh.tenMon); 
    for (int i = 0; i < dsMon->count; i++) {
        if (strcmp(dsMon->A[i].tenMon, mh.tenMon) == 0) {
            printf("Mon hoc da ton tai!\n");
            return;
        }
    }

    dsMon->A[dsMon->count++] = mh;
    printf("Da them mon hoc thanh cong!\n");
}

float diemHe10SangHe4(float diem10) {
    if (diem10 >= 9.0) return 4.0;
    if (diem10 >= 8.5) return 3.7;
    if (diem10 >= 8.0) return 3.5;
    if (diem10 >= 7.0) return 3.0;
    if (diem10 >= 6.5) return 2.5;
    if (diem10 >= 5.5) return 2.0;
    if (diem10 >= 5.0) return 1.5;
    if (diem10 >= 4.0) return 1.0;
    return 0.0;
}

float tinhDiemTB10(struct Sinhvien sv) {
    if (sv.soMon == 0) return 0.0;
    float tongDiem = 0;
    for (int i = 0; i < sv.soMon; i++) {
        tongDiem += sv.diem[i];
    }
    return tongDiem / sv.soMon;
}

float tinhGPA(struct Sinhvien sv) {
    if (sv.soMon == 0) return 0.0;
    float tongDiemHe4 = 0;
    for (int i = 0; i < sv.soMon; i++) {
        tongDiemHe4 += diemHe10SangHe4(sv.diem[i]);
    }
    return tongDiemHe4 / sv.soMon;
}

void xepLoaiHocLuc(float gpa, char *hocLuc) {
    if (gpa >= 3.6) {
        strcpy(hocLuc, "Xuat sac");
    } else if (gpa >= 3.2) {
        strcpy(hocLuc, "Gioi");
    } else if (gpa >= 2.5) {
        strcpy(hocLuc, "Kha");
    } else if (gpa >= 2.0) {
        strcpy(hocLuc, "Trung Binh");
    } else {
        strcpy(hocLuc, "Yeu");
    }
}

void nhapDiemChoSinhVien(List *L, MonHocList dsMon) {
    if (EMPTY_LIST(*L)) {
        printf("Danh sach sinh vien rong!\n");
        return;
    }

    if (dsMon.count == 0) {
        printf("Chua co mon hoc nao trong he thong!\n");
        return;
    }

    for (int i = 0; i < L->Last; i++) {
        struct Sinhvien *sv = &L->A[i];
        printf("\nNhap diem cho sinh vien: %s - %s\n", sv->id, sv->name);
        sv->soMon = dsMon.count;

        for (int j = 0; j < dsMon.count; j++) {
            float diem;
            do {
                printf(">> Diem mon %-25s: ", dsMon.A[j].tenMon);
                scanf("%f", &diem);
                if (diem < 0 || diem > 10) {
                    printf("Diem khong hop le! Nhap lai (0-10)\n");
                }
            } while (diem < 0 || diem > 10);
            sv->diem[j] = diem;
        }
        
        sv->gpa = tinhGPA(*sv);
        xepLoaiHocLuc(sv->gpa, sv->hocLuc);
    }

    printf("\nNhap diem thanh cong cho tat ca sinh vien!\n");
}


void hienThiKetQuaHocTap(List L, MonHocList dsMon) {
    if (L.Last == 0) {
        printf("Danh sach rong!\n");
        return;
    }
    
    if (dsMon.count == 0) {
        printf("Chua co mon hoc nao de tinh diem!\n");
        PRINT_LIST(L); 
        return;
    }

    printf("\n+-----+--------------+---------------------------+------------+------------+----------------+\n");
    printf("| STT | MSSV         | Ho Ten                    | Diem TB 10 | Diem TB 4  | Xep Loai       |\n");
    printf("+-----+--------------+---------------------------+------------+------------+----------------+\n");

    for (int i = 0; i < L.Last; i++) {
        struct Sinhvien sv = L.A[i];
        float diem10 = tinhDiemTB10(sv);
        
        printf("| %-3d | %-12s | %-25s | %-10.2f | %-10.2f | %-14s |\n",
               i + 1, sv.id, sv.name, diem10, sv.gpa, sv.hocLuc);
    }

    printf("+-----+--------------+---------------------------+------------+------------+----------------+\n");
}

void SORT_BY_HOCLUC(List *L) {
    if (L->Last == 0 || L->A[0].soMon == 0) {
        printf("Chua co sinh vien hoac chua nhap diem de xep loai!\n");
        return;
    }
    
    for (int i = 0; i < L->Last - 1; i++) {
        for (int j = i + 1; j < L->Last; j++) {
            if (L->A[i].gpa < L->A[j].gpa) {
                struct Sinhvien tmp = L->A[i];
                L->A[i] = L->A[j];
                L->A[j] = tmp;
            } 
            else if (L->A[i].gpa == L->A[j].gpa) {
                if (tinhDiemTB10(L->A[i]) < tinhDiemTB10(L->A[j])) {
                    struct Sinhvien tmp = L->A[i];
                    L->A[i] = L->A[j];
                    L->A[j] = tmp;
                }
            }
        }
    }
    printf("Da sap xep danh sach sinh vien theo Hoc luc (GPA) giam dan.\n");
}
 
 
// ================== MAIN ==================
int main() {
 
    List L;
    MAKENULL_LIST(&L);
    
    MonHocList dsMon;
    dsMon.count = 0;
 
 
 
    int choice;
    
      printf("\n+=================================================================+\n");
        printf("|              HE THONG QUAN LY SINH VIEN                         |\n");
        printf("+=================================================================+\n");
        printf("| [1] Them sinh vien vao danh sach                		  |\n");
        printf("| [2] Xoa sinh vien theo MSV                    		  |\n");
        printf("| [3] Nhap diem cho cac sinh vien                                 |\n");
        printf("| [4] Tim kiem sinh vien theo MSV              			  |\n");
        printf("| [5] Sap xep danh sach theo ten                       		  |\n");
        printf("| [6] In danh sach sinh vien                                      |\n");
        printf("| [7] Them mon hoc moi vao danh sach                              |\n");
        printf("| [8] Sap xep danh sach theo hoc luc (GPA)                        |\n"); 
        printf("| [9] Chinh sua diem sinh vien theo MSV	                  |\n");
        printf("| [10]Clear man hinh                            |\n");
        printf("| [0] Thoat chuong trinh                                          |\n");
        printf("+=================================================================+\n");
    while (1) {
      
        printf("\n>> Nhap lua chon cua ban: ");
        scanf("%d", &choice);
 
        if (choice == 0) {
            printf("Da thoat\n");
            break;
        }
        switch (choice) {
            case 1: {
                struct Sinhvien sv = nhapSinhVien(L);
                Position p;
                printf("Nhap Vi Tri Sinh Vien Muon Them Chen Vao (Dau: 1, Cuoi: 2): ");
                scanf("%d", &p);
                if(p == 1 ){
                    INSERT_LIST(sv, 1, &L); 
                    printf("Them sinh vien vao thanh cong. \n");
                }
                else if(p == 2){
                    INSERT_LIST(sv, END(L), &L);
                    printf("Them sinh vien vao thanh cong. \n"); 
                }
                else{
                    printf("Lua chon khong hop le \n");
                }
                break;
            }
            case 2: {
                char id[20];
                printf("\n+-----------------------------------------+\n");
                printf("|      XOA SINH VIEN THEO MA SINH VIEN    |\n");
                printf("+-----------------------------------------+\n");
                printf(">> Nhap MSV can xoa: ");
                scanf("%s", id);
                DELETE_BY_ID(id, &L);
                break;
            }
            case 3: {
                printf("\n+---------------------------------------------+\n");
                printf("|          NHAP DIEM CHO CAC SINH VIEN        |\n");
                printf("+---------------------------------------------+\n");
                nhapDiemChoSinhVien(&L, dsMon);
                break;
            }
            case 4: {
 
                char id[20];
                printf("\n+-----------------------------------------+\n");
                printf("|        TIM KIEM SINH VIEN THEO MSV      |\n");
                printf("+-----------------------------------------+\n");
                printf(">> Nhap MSV: ");
                scanf("%s", id);
                Position p = LOCATE(id, L);
                if (p == END(L)) {
                 printf("   Khong tim thay sinh vien co MSV: %s\n", id);
                 
             } else {
                 struct Sinhvien sv = RETRIEVE(p, L);
                      printf("   Da tim thay sinh vien trong danh sach                                  \n");
                      printf("+==========================================================================+\n");
                      printf("|   Thong tin sinh vien:                                                   |\n");
                      printf("|   MSSV      : %-59s|\n", sv.id);
                      printf("|   Ho ten    : %-59s|\n", sv.name);
                      printf("|   Ngay sinh : %-27sTuoi : %-11d              |\n", sv.ns, sv.tuoi);
                      printf("+==========================================================================+\n");
             }
             break;
            }
            case 5: 
                
                 SORT_BY_NAME(&L);
                 PRINT_LIST(L);
                break;
            case 6:
                printf("\n+---------------------------------------------+\n");
                printf("|      KET QUA HOC TAP CUA SINH VIEN          |\n");
                printf("+---------------------------------------------+\n");
                hienThiKetQuaHocTap(L, dsMon);
                break;
            case 7:
                printf("\n+-----------------------------------------+\n");
                printf("|           THEM MON HOC MOI              |\n");
                printf("+-----------------------------------------+\n");
                themMonHoc(&dsMon); 
                break;
            case 8: { 
                 printf("\n+---------------------------------------------+\n");
                printf("|      SAP XEP SINH VIEN THEO HOC LUC         |\n");
                printf("+---------------------------------------------+\n");
                SORT_BY_HOCLUC(&L);
                hienThiKetQuaHocTap(L, dsMon); 
                break;    
            }
            case 9:  {
			    char id[20];
			    int found = 0;
			
			    printf("\n+---------------------------------------------+\n");
			    printf("|       CHINH SUA DIEM SINH VIEN THEO MSV     |\n");
			    printf("+---------------------------------------------+\n");
			    printf(">> Nhap MSV can chinh sua: ");
			    scanf("%s", id);
			
			    for (int i = 0; i < L.Last; i++) {
			        if (strcmp(L.A[i].id, id) == 0) {
			            found = 1;
			            struct Sinhvien *sv = &L.A[i];
			            printf("\nThong tin sinh vien:\n");
			            printf("MSSV: %s\n", sv->id);
			            printf("Ho ten: %s\n", sv->name);
			            printf("So mon hoc hien co: %d\n", sv->soMon);
			
			            if (sv->soMon == 0) {
			                printf("Sinh vien chua co diem mon hoc nao de chinh sua!\n");
			                break;
			            }
			
			            printf("\nCac diem hien tai:\n");
			            for (int j = 0; j < sv->soMon; j++) {
			                printf("  Mon %d: %.2f\n", j + 1, sv->diem[j]);
			            }
			
			            int mon;
			            printf("\n>> Nhap thu tu mon muon chinh sua (1-%d): ", sv->soMon);
			            scanf("%d", &mon);
			
			            if (mon >= 1 && mon <= sv->soMon) {
			                float diemMoi;
			                do {
			                    printf(">> Nhap diem moi cho mon %d (0-10): ", mon);
			                    scanf("%f", &diemMoi);
			                    if (diemMoi < 0 || diemMoi > 10)
			                        printf("Diem khong hop le, vui long nhap lai!\n");
			                } while (diemMoi < 0 || diemMoi > 10);
			                sv->diem[mon - 1] = diemMoi;
			            } else {
			                printf("So thu tu mon khong hop le!\n");
			                break;
			            }
			
			            sv->gpa = tinhGPA(*sv);
			            xepLoaiHocLuc(sv->gpa, sv->hocLuc);
			
			            printf("\nDa cap nhat diem cho sinh vien co MSV %s.\n", id);
			            printf("GPA moi: %.2f | Hoc luc: %s\n", sv->gpa, sv->hocLuc);
			            break;
			        }
			    }
			
			    if (!found) printf("\nKhong tim thay sinh vien co MSV %s!\n", id);
			
			    
	
			break;
			    }
              
            
            case 10: {
                	system(CLEAR);
   				printf("+==============================================================+\n");
   				printf("|            HE THONG QUAN LY SINH VIEN                        |\n");
  				printf("+==============================================================+\n");
  				printf("| [1] Them sinh vien vao danh sach                             |\n");
 				printf("| [2] Xoa sinh vien theo MSV                                   |\n");
  				printf("| [3] Nhap diem cho cac sinh vien                              |\n");
   				printf("| [4] Tim kiem sinh vien theo MSV                              |\n");
   				printf("| [5] Sap xep danh sach theo ten                               |\n");
  				printf("| [6] In danh sach sinh vien                                   |\n");
  			 	printf("| [7] Them mon hoc moi vao danh sach                           |\n");
   				printf("| [8] Xem ket qua hoc tap (Diem TB 10, GPA, Xep loai)          |\n");
  			    printf("| [9] Sap xep danh sach theo hoc luc (GPA)                     |\n");
  				printf("| [10] Clear man hinh (giu nguyen du lieu)                     |\n");
  				printf("| [11] Chinh sua diem sinh vien theo MSV                       |\n");
  				printf("| [0] Thoat chuong trinh                                       |\n");
   				printf("+==============================================================+\n");
   				printf("Man hinh da duoc lam moi.\n");
				break;
			}
            default:
                printf("Lua chon khong hop le\n");
           
    }}
    return 0;
}


