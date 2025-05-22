#include<stdio.h>
#include"Chuongtrinhdaotao.h"

//#define MAX_SV 1000
#define MAX_tinchidk 28

struct monhoc;
struct Nganhdaotao;

struct sinhvien{
    char name[20];
    int mssv;
    char manganh[10];
};

struct MonHocNode{
    monhoc mh;
    MonHocNode* next;
};

struct dky{
    int mssv;
    char hocki[10];
    MonHocNode* dsmondk;
    int somon;
    int tongsotinchi;
};

//Ham tim nganh dao tao
Nganhdaotao* timNganhdaotao(Nganhdaotao dsndt[], int soNDT, char manganh[]){
    for (int i = 0; i < soNDT; i++) {
        if (strcmp(dsndt[i].manganh, manganh) == 0) {
            return &dsndt[i];
        }
    }
    return NULL;
}

//Ham tim mon hoc
monhoc* timMonHoc(Nganhdaotao *ndt, char maHP[]) {
    for (int i = 0; i < ndt->somonhoc; i++) {
        if (strcmp(ndt->mh[i].mahp, maHP) == 0) {
            return &ndt->mh[i];
        }
    }
    return NULL;
}

int ktraMonDky(MonHocNode* list, char maHP[]){
    MonHocNode* temp = list;
    while(temp != NULL){
        if(strcmp(temp->mh.mahp, maHP) == 0){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void themMonHoc(dky* dk, monhoc* mh){
    MonHocNode* newNode = (MonHocNode*)malloc(sizeof(MonHocNode));
    newNode->mh = *mh;
    newNode->next = dk->dsmondk;
    dk->dsmondk = newNode;
    dk->somon++;
    dk->tongsotinchi += mh->tinchi;
}

void dkyhp(dky *dk, sinhvien *sv, Nganhdaotao *ctdt) {
    char maHP[10];
    int tiepTuc = 1;
    
    printf("\n=== DANG KY HOC PHAN CHO SINH VIEN %d ===", sv->mssv);
    printf("\nNhap 'exit' de ket thuc dang ky\n");

    while(tiepTuc) {
        // Hiển thị trạng thái hiện tại
        printf("\nTong tin chi hien tai: %d/%d", dk->tongsotinchi, MAX_tinchidk);
        printf("\nNhap ma hoc phan: ");
        scanf("%9s", maHP); // Giới hạn nhập 9 ký tự + null terminator

        // Kiểm tra điều kiện thoát
        if(strcmp(maHP, "exit") == 0) {
            tiepTuc = 0;
            continue;
        }

        // Tìm môn học trong CTDT
        monhoc *mh = timMonHoc(ctdt, maHP);
        
        if(mh == NULL) {
            printf("Ma hoc phan khong ton tai!\n");
            continue;
        }

        // Kiểm tra trùng môn
        if(ktraMonDky(dk->dsmondk, maHP)){
            printf("Mon da duoc dang ky!\n");
            continue;
        }

        // Kiểm tra số tín chỉ
        if(dk->tongsotinchi + mh->tinchi > MAX_tinchidk) {
            printf("!!!Vuot qua tin chi toi da (%d + %d > %d)!\n", 
                  dk->tongsotinchi, mh->tinchi, MAX_tinchidk);
            continue;
        }

        // Thêm vào danh sách đăng ký
        themMonHoc(dk, mh);
        printf("-> Dang ky thanh cong: %s - %s (%dTC)\n", 
              mh->mahp, mh->tenhp, mh->tinchi);
    }
    
    printf("\nDa hoan tat dang ky!\n");
}


void hienThiDangKy(dky dk) {
    printf("\nTHONG TIN DANG KY\n");
    printf("MSSV: %d\n", dk.mssv);
    printf("Hoc ky: %s\n", dk.hocki);
    printf("Tong tin chi: %d/%d\n", dk.tongsotinchi, MAX_tinchidk);
    printf("Danh sach mon hoc:\n");
    printf("%-10s %-30s %-10s\n", "Ma HP", "Ten mon hoc", "Tin chi");
    
    MonHocNode* temp = dk.dsmondk;
    while(temp != NULL){
        printf("%-10s %-30s %-10d\n", temp->mh.mahp, temp->mh.tenhp, temp->mh.tinchi);
        temp = temp->next;
    }
}

int main() {
    // Khởi tạo dữ liệu mẫu
    Nganhdaotao cntt = {
        "CNTT", "Cong nghe thong tin", 10, 4, 
        {
            {"CS101", "Lap trinh C", 3},
            {"CS102", "Cau truc du lieu", 4},
            {"CS103", "Toan roi rac", 3}
        },
        3
    };

    sinhvien sv1 = {"Nguyen Van A", 20240001, "CNTT"};
    dky dangky1 = {20240001, "HK1_2024", {}, 0, 0};

    Nganhdaotao dsNDT[] = {cntt};

    // Đăng ký học phần
    dkyhp(&dangky1, &sv1, dsNDT);
    dkyhp(&dangky1, &sv1, dsNDT);

    // Hiển thị kết quả
    hienThiDangKy(dangky1);

    return 0;
}
