#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define MAX_MHP_LENGTH 10
#define MAX_TENHP_LENGTH 50
#define MAX_MANGANH_LENGTH 10
#define MAX_TENNGANH_LENGTH 100

struct monhoc {
    char mahp[MAX_MHP_LENGTH];
    char tenhp[MAX_TENHP_LENGTH];  
    int tinchi;
};

struct Nganhdaotao {
    char manganh[MAX_MANGANH_LENGTH];
    char tennganh[MAX_TENNGANH_LENGTH];
    int sotinchi;
    float thoigiandaotao;
    monhoc mh[MAX];
    int somonhoc;
};

struct Node {
    Nganhdaotao ndt;
    Node* next;
};

typedef Node* PNode;
typedef Node* LinkedList;

// Khởi tạo danh sách rỗng
void initList(LinkedList& list) {
    list = NULL;
}

// Kiểm tra danh sách rỗng
int isEmpty(LinkedList list) {
    return (list == NULL);
}

// Tạo node mới
PNode createNode(Nganhdaotao ndt) {
    PNode newNode = (PNode)malloc(sizeof(Node));
    newNode->ndt = ndt;
    newNode->ndt.somonhoc = 0;
    newNode->ndt.sotinchi = 0;
    newNode->next = NULL;
    return newNode;
}

// Hàm nhập thông tin môn học từ bàn phím
void inputMonHoc(monhoc* mh) {
    printf("\nNhap ma hoc phan: ");
    scanf("%9s", mh->mahp);
    getchar();
    
    printf("\nNhap ten mon hoc: ");
    fgets(mh->tenhp, MAX_TENHP_LENGTH, stdin);
    mh->tenhp[strcspn(mh->tenhp, "\n")] = '\0';
    
    printf("\nNhap so tin chi: ");
    scanf("%d", &mh->tinchi);
}

// Hàm nhập thông tin ngành từ bàn phím
void inputNganhDaoTao(Nganhdaotao* ndt) {
    printf("\nNhap ma nganh: ");
    scanf("%9s", ndt->manganh);
    getchar(); // Xóa bộ đệm
    
    printf("\nNhap ten nganh: ");
    fgets(ndt->tennganh, MAX_TENNGANH_LENGTH, stdin);
    ndt->tennganh[strcspn(ndt->tennganh, "\n")] = '\0'; // Xóa ký tự newline
    
    printf("\nNhap thoi gian dao tao (nam): ");
    scanf("%f", &ndt->thoigiandaotao);
    
    ndt->sotinchi = 0;
    ndt->somonhoc = 0;
}

// Thêm ngành đào tạo vào danh sách
void insertNDT(LinkedList& list, Nganhdaotao ndt) {
    PNode newNode = createNode(ndt);
    if (isEmpty(list)) {
        list = newNode;
    } 
    else {
        PNode temp = list;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Thêm môn học vào ngành đào tạo
void insertmonhoc(LinkedList list, char* manganh, char* mahp, char* tenhp, int tinchi) {
    if (list == NULL) {
        printf("\nDanh sach nganh rong!\n");
        return;
    }

    // Tìm ngành theo mã ngành
    PNode p = list;
    while (p != NULL && strcmp(p->ndt.manganh, manganh) != 0) {
        p = p->next;
    }

    if (p == NULL) {
        printf("\nKhong tim thay nganh %s!\n", manganh);
        return;
    }

    if (mahp == NULL || tenhp == NULL) {
        printf("\nMã học phần hoặc tên học phần không hợp lệ!\n");
        return;
    }

    if (p->ndt.somonhoc >= MAX) {
        printf("\nDanh sách môn học đã đầy!\n");
        return;
    }

    for (int i = 0; i < p->ndt.somonhoc; i++) {
        if (strcmp(p->ndt.mh[i].mahp, mahp) == 0) {
            printf("\nMã học phần bị trùng!\n");
            return;
        }
    }

    if (tinchi <= 0 || tinchi > 10) {
        printf("\nSố tín chỉ không hợp lệ!\n");
        return;
    }
    
    strncpy(p->ndt.mh[p->ndt.somonhoc].mahp, mahp, MAX_MHP_LENGTH - 1);
    p->ndt.mh[p->ndt.somonhoc].mahp[MAX_MHP_LENGTH - 1] = '\0';
    strncpy(p->ndt.mh[p->ndt.somonhoc].tenhp, tenhp, MAX_TENHP_LENGTH - 1);
    p->ndt.mh[p->ndt.somonhoc].tenhp[MAX_TENHP_LENGTH - 1] = '\0';
    p->ndt.mh[p->ndt.somonhoc].tinchi = tinchi; 
    p->ndt.somonhoc++;
    p->ndt.sotinchi += tinchi;
    printf("\nĐã thêm môn học '%s' (%s, %d TC) vào ngành %s\n", tenhp, mahp, tinchi, p->ndt.tennganh);
}

// Tìm kiếm ngành đào tạo bằng mã ngành
PNode searchNganh(LinkedList list, char manganh[]) {
    PNode p = list;
    while (p != NULL) {
        if (strcmp(p->ndt.manganh, manganh) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// Xóa một ngành đào tạo bằng mã ngành
void deleteNganh(LinkedList& list, char manganh[]) {
    if (isEmpty(list)) {
        printf("Danh sach rong!\n");
        return;
    }
    
    PNode p = list;
    PNode prev = NULL;
    
    // Nếu node cần xóa là node đầu tiên
    if (strcmp(p->ndt.manganh, manganh) == 0) {
        list = p->next;
        free(p);
        printf("Da xoa nganh %s\n", manganh);
        return;
    }
    
    // Tìm node cần xóa
    while (p != NULL && strcmp(p->ndt.manganh, manganh) != 0) {
        prev = p;
        p = p->next;
    }
    
    if (p == NULL) {
        printf("Khong tim thay nganh %s\n", manganh);
        return;
    }
    
    // Bỏ qua node cần xóa
    prev->next = p->next;
    free(p);
    printf("Da xoa nganh %s\n", manganh);
}

// Tìm kiếm môn học bằng mã học phần
void searchMonHoc(LinkedList list, char mahp[]) {
    PNode p = list;
    int found = 0;
    
    printf("\nKet qua tim kiem mon hoc co ma %s:\n", mahp);
    printf("----------------------------------------------------\n");
    printf("| %-8s | %-30s | %-8s | %-8s |\n", 
           "Ma nganh", "Ten nganh", "Ten mon", "Tin chi");
    printf("----------------------------------------------------\n");
    
    while (p != NULL) {
        for (int i = 0; i < p->ndt.somonhoc; i++) {
            if (strcmp(p->ndt.mh[i].mahp, mahp) == 0) {
                printf("| %-8s | %-30s | %-8s | %-8d |\n", 
                       p->ndt.manganh, p->ndt.tennganh, 
                       p->ndt.mh[i].tenhp, p->ndt.mh[i].tinchi);
                found = 1;
            }
        }
        p = p->next;
    }
    
    if (!found) {
        printf("Khong tim thay mon hoc co ma %s\n", mahp);
    }
    printf("----------------------------------------------------\n");
}

// Hiểu thị môn học của một ngành
void displayMonHoc(LinkedList list, char manganh[]) {
    PNode p = list;
    while (p != NULL) {
        if (strcmp(p->ndt.manganh, manganh) == 0) {
            printf("\nDANH SACH MON HOC CUA NGANH %s:\n", manganh);
            printf("----------------------------------------------------\n");
            printf("| %-8s | %-30s | %-8s |\n", "Ma HP", "Ten mon hoc", "Tin chi");
            printf("----------------------------------------------------\n");
            
            for (int i = 0; i < p->ndt.somonhoc; i++) {
                printf("| %-8s | %-30s | %-8d |\n", 
                       p->ndt.mh[i].mahp, 
                       p->ndt.mh[i].tenhp, 
                       p->ndt.mh[i].tinchi);
            }
            printf("----------------------------------------------------\n");
            return;
        }
        p = p->next;
    }
    printf("Khong tim thay nganh %s\n", manganh);
}

// Hiển thị tất cả các ngành
void displayAllNganh(LinkedList list) {
    printf("\nDANH SACH NGANH DAO TAO:\n");
    printf("-----------------------------------------------------------------\n");
    printf("| %-8s | %-30s | %-8s | %-6s | %-8s |\n", 
           "Ma nganh", "Ten nganh", "So TC", "TG DT", "So mon");
    printf("-----------------------------------------------------------------\n");
    
    PNode p = list;
    while (p != NULL) {
        printf("| %-8s | %-30s | %-8d | %-6.1f | %-8d |\n", 
               p->ndt.manganh, p->ndt.tennganh, 
               p->ndt.sotinchi, p->ndt.thoigiandaotao, 
               p->ndt.somonhoc);
        p = p->next;
    }
    printf("-----------------------------------------------------------------\n");
}

// Hàm hiển thị lựa chọn
void menu() {
    printf("\n=== HE THONG QUAN LY DAO TAO DAI HOC ===\n");
    printf("1. Them nganh dao tao\n");
    printf("2. Them mon hoc vao nganh\n");
    printf("3. Hien thi tat ca nganh dao tao\n");
    printf("4. Hien thi mon hoc theo nganh\n");
    printf("5. Tim kiem nganh theo ma\n");
    printf("6. Tim kiem mon hoc theo ma\n");
    printf("7. Xoa mot nganh\n");
    printf("0. Thoat\n");
    printf("=========================================\n");
    printf("Lua chon cua ban: ");
}

int main() {
    LinkedList list;
    initList(list);
    int choice;
    char manganh[MAX_MANGANH_LENGTH];
    char mahp[MAX_MHP_LENGTH];
    
    do {
        menu();
        scanf("%d", &choice);
        getchar(); // Xóa bộ đệm
        
        switch (choice) {
            case 1: {
                Nganhdaotao ndt;
                inputNganhDaoTao(&ndt);
                insertNDT(list, ndt);
                printf("Da them nganh %s vao he thong.\n", ndt.manganh);
                break;
            }
            case 2: {
                monhoc mh;
                printf("Nhap ma nganh can them mon hoc: ");
                scanf("%9s", manganh);
                getchar();
    
                inputMonHoc(&mh);
                insertmonhoc(list, manganh, mh.mahp, mh.tenhp, mh.tinchi); // Đã sửa
                break;
            }
            case 3: {
                displayAllNganh(list);
                break;
            }
            case 4: {
                printf("Nhap ma nganh can hien thi mon hoc: ");
                scanf("%9s", manganh);
                displayMonHoc(list, manganh);
                break;
            }
            case 5: {
                printf("Nhap ma nganh can tim: ");
                scanf("%9s", manganh);
                PNode found = searchNganh(list, manganh);
                if (found != NULL) {
                    printf("\nTim thay nganh:\n");
                    printf("Ma nganh: %s\n", found->ndt.manganh);
                    printf("Ten nganh: %s\n", found->ndt.tennganh);
                }
                break;
            }
            case 6: {
                printf("Nhap ma hoc phan can tim: ");
                scanf("%9s", mahp);
                searchMonHoc(list, mahp);
                break;
            }
            case 7: {
                printf("Nhap ma nganh can xoa: ");
                scanf("%9s", manganh);
                deleteNganh(list, manganh);
                break;
            }
            case 0: {
                printf("Thoat chuong trinh...\n");
                break;
            }
            default: {
                printf("Lua chon khong hop le!\n");
            }
        }
    } while (choice != 0);
    
    //freeList(&list);
    return 0;
}