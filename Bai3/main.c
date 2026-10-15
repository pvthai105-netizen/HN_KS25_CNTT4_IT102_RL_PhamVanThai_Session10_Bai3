#include <stdio.h>
#include <string.h>

#define MAX_ZONE 10
#define MAX_QR 100
#define MAX_MUA 4

struct TicketZone {
    int zone_id;
    char zone_name[30];
    float ticket_price;
    int total_capacity;
    int sold_tickets;
};

struct QrCheckIn {
    char qr_code[20];
    int zone_id;
    int is_used;
};

// Khai bao prototype
int timKhuVuc(struct TicketZone dsZone[], int total_zones, int zone_id);
float tinhGiaVe(float ticket_price, int is_early_bird);
int banVe(struct TicketZone dsZone[], int total_zones,
          int zone_id, int quantity, int is_early_bird);
int timQR(struct QrCheckIn dsQR[], int total_qrs, char qr_code[]);
int checkInQR(struct TicketZone dsZone[], int total_zones,
              struct QrCheckIn dsQR[], int total_qrs, char qr_code[]);

int main(void) {
    struct TicketZone dsZone[MAX_ZONE] = {
        {1, "VIP", 2000000, 100, 98},
        {2, "Zone A", 1200000, 200, 100}
    };

    struct QrCheckIn dsQR[MAX_QR] = {
        {"QR001", 1, 0},
        {"QR002", 1, 1},
        {"QR003", 2, 0}
    };

    int total_zones = 2;
    int total_qrs = 3;

    printf("=== TICKETBOX LIVE CONCERT ===\n");

    printf("\n1. MUA 2 VE VIP, EARLY BIRD\n");
    banVe(dsZone, total_zones, 1, 2, 1);

    printf("\n2. MUA 5 VE VIP\n");
    banVe(dsZone, total_zones, 1, 5, 0);

    printf("\n3. MUA 3 VE VIP KHI CHI CON 2 VE\n");
    banVe(dsZone, total_zones, 1, 3, 0);

    printf("\n4. MUA VE O KHU VUC KHONG TON TAI\n");
    banVe(dsZone, total_zones, 99, 1, 0);

    printf("\n5. MUA SO LUONG AM\n");
    banVe(dsZone, total_zones, 2, -2, 0);

    printf("\n6. CHECK-IN QR001\n");
    checkInQR(dsZone, total_zones, dsQR, total_qrs, "QR001");

    printf("\n7. QUET LAI QR001\n");
    checkInQR(dsZone, total_zones, dsQR, total_qrs, "QR001");

    printf("\n8. CHECK-IN QR KHONG TON TAI\n");
    checkInQR(dsZone, total_zones, dsQR, total_qrs, "QR999");

    printf("\n9. CHECK-IN QR002 DA SU DUNG\n");
    checkInQR(dsZone, total_zones, dsQR, total_qrs, "QR002");

    printf("\n10. TONG KET SO VE DA BAN\n");
    for (int i = 0; i < total_zones; i++) {
        printf("%s: %d/%d ve\n",
               dsZone[i].zone_name,
               dsZone[i].sold_tickets,
               dsZone[i].total_capacity);
    }

    return 0;
}

// Tim khu vuc theo ma
int timKhuVuc(struct TicketZone dsZone[], int total_zones, int zone_id) {
    for (int i = 0; i < total_zones; i++) {
        if (dsZone[i].zone_id == zone_id) {
            return i;
        }
    }

    return -1;
}

// Tinh gia ve
float tinhGiaVe(float ticket_price, int is_early_bird) {
    if (is_early_bird == 1) {
        return ticket_price * 0.85f;
    }

    return ticket_price;
}

// Xu ly ban ve
int banVe(struct TicketZone dsZone[], int total_zones,
          int zone_id, int quantity, int is_early_bird) {
    if (total_zones <= 0) {
        printf("[LOI] Danh sach khu vuc dang rong!\n");
        return 0;
    }

    if (quantity < 1 || quantity > MAX_MUA) {
        printf("[LOI] Moi giao dich chi duoc mua tu 1 den 4 ve!\n");
        return 0;
    }

    int viTri = timKhuVuc(dsZone, total_zones, zone_id);

    if (viTri == -1) {
        printf("[LOI] Khu vuc khong ton tai!\n");
        return 0;
    }

    if (dsZone[viTri].sold_tickets + quantity >
        dsZone[viTri].total_capacity) {
        printf("[LOI] Khong du ve trong khu vuc!\n");
        return 0;
    }

    float giaVe = tinhGiaVe(dsZone[viTri].ticket_price, is_early_bird);
    float tongTien = giaVe * quantity;

    dsZone[viTri].sold_tickets += quantity;

    printf("[THANH CONG] Da ban %d ve khu vuc %s.\n",
           quantity, dsZone[viTri].zone_name);
    printf("Gia moi ve: %.0f VND\n", giaVe);
    printf("Tong tien: %.0f VND\n", tongTien);

    return 1;
}

// Tim QR theo ma
int timQR(struct QrCheckIn dsQR[], int total_qrs, char qr_code[]) {
    for (int i = 0; i < total_qrs; i++) {
        if (strcmp(dsQR[i].qr_code, qr_code) == 0) {
            return i;
        }
    }

    return -1;
}

// Xu ly check-in QR
int checkInQR(struct TicketZone dsZone[], int total_zones,
              struct QrCheckIn dsQR[], int total_qrs, char qr_code[]) {
    if (total_qrs <= 0 || total_zones <= 0) {
        printf("[LOI] Danh sach khu vuc hoac QR dang rong!\n");
        return 0;
    }

    int viTriQR = timQR(dsQR, total_qrs, qr_code);

    if (viTriQR == -1) {
        printf("[LOI] Ma QR khong ton tai!\n");
        return 0;
    }

    if (timKhuVuc(dsZone, total_zones,
                  dsQR[viTriQR].zone_id) == -1) {
        printf("[LOI] Khu vuc cua QR khong ton tai!\n");
        return 0;
    }

    if (dsQR[viTriQR].is_used == 1) {
        printf("[CANH BAO] QR da duoc su dung! Tu choi check-in.\n");
        return 0;
    }

    dsQR[viTriQR].is_used = 1;

    printf("[THANH CONG] Check-in QR %s thanh cong!\n", qr_code);

    return 1;
}