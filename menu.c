#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_MEMBERS 100
#define BOOK_FILE "books.txt"
#define MEMBER_FILE "members.txt"

// Struct Definitions
typedef struct {
    int id;
    char title[100];
    char author[100];
    int year;
    int is_borrowed;
} Book;

typedef struct {
    int id;
    char name[100];
    char email[100];
} Member;

// Global Variables
Book books[MAX_BOOKS];
int book_count = 0;

Member members[MAX_MEMBERS];
int member_count = 0;

// Function Prototypes
void load_books_from_file();
void save_books_to_file();
void load_members_from_file();
void save_members_to_file();

void add_book();
void list_books();
void delete_book();
void borrow_book();
void return_book();

void add_member();
void list_members();

void calculate_late_fee();

void menu();

int main() {
    load_books_from_file();
    load_members_from_file();
    menu();
    save_books_to_file();
    save_members_to_file();
    return 0;
}

// Load books from file
void load_books_from_file() {
    FILE *file = fopen(BOOK_FILE, "r");
    if (file == NULL) {
        printf("Kitap dosyası bulunamadı, yeni bir dosya oluşturulacak.\n");
        return;
    }

    while (fscanf(file, "%d,%99[^,],%99[^,],%d,%d\n", &books[book_count].id, books[book_count].title, 
                  books[book_count].author, &books[book_count].year, &books[book_count].is_borrowed) == 5) {
        book_count++;
    }
    fclose(file);
}

// Save books to file
void save_books_to_file() {
    FILE *file = fopen(BOOK_FILE, "w");
    if (file == NULL) {
        printf("Kitap dosyası kaydedilirken bir hata oluştu.\n");
        return;
    }

    for (int i = 0; i < book_count; i++) {
        fprintf(file, "%d,%s,%s,%d,%d\n", books[i].id, books[i].title, books[i].author, books[i].year, books[i].is_borrowed);
    }

    fclose(file);
}

// Load members from file
void load_members_from_file() {
    FILE *file = fopen(MEMBER_FILE, "r");
    if (file == NULL) {
        printf("Üye dosyası bulunamadı, yeni bir dosya oluşturulacak.\n");
        return;
    }

    while (fscanf(file, "%d,%99[^,],%99[^\n]\n", &members[member_count].id, members[member_count].name, 
                  members[member_count].email) == 3) {
        member_count++;
    }
    fclose(file);
}

// Save members to file
void save_members_to_file() {
    FILE *file = fopen(MEMBER_FILE, "w");
    if (file == NULL) {
        printf("Üye dosyası kaydedilirken bir hata oluştu.\n");
        return;
    }

    for (int i = 0; i < member_count; i++) {
        fprintf(file, "%d,%s,%s\n", members[i].id, members[i].name, members[i].email);
    }

    fclose(file);
}

// Add a new book
void add_book() {
    if (book_count >= MAX_BOOKS) {
        printf("Kitap sınırına ulaşıldı!\n");
        return;
    }

    Book new_book;
    new_book.id = (book_count > 0) ? books[book_count - 1].id + 1 : 1;

    printf("Kitap Başlığı: ");
    getchar(); // Clear input buffer
    fgets(new_book.title, 100, stdin);
    new_book.title[strcspn(new_book.title, "\n")] = '\0';

    printf("Yazar: ");
    fgets(new_book.author, 100, stdin);
    new_book.author[strcspn(new_book.author, "\n")] = '\0';

    printf("Basım Yılı: ");
    scanf("%d", &new_book.year);

    new_book.is_borrowed = 0;

    books[book_count++] = new_book;
    printf("Kitap başarıyla eklendi!\n");
}

// List all books
void list_books() {
    if (book_count == 0) {
        printf("Henüz hiç kitap eklenmemiş.\n");
        return;
    }

    printf("\n--- Kitap Listesi ---\n");
    for (int i = 0; i < book_count; i++) {
        printf("ID: %d | Başlık: %s | Yazar: %s | Yıl: %d | Durum: %s\n",
               books[i].id, books[i].title, books[i].author, books[i].year,
               books[i].is_borrowed ? "Ödünç Verildi" : "Mevcut");
    }
}

// Delete a book
void delete_book() {
    int id;
    printf("Silmek istediğiniz kitabın ID'sini girin: ");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Bu ID'ye sahip bir kitap bulunamadı.\n");
        return;
    }

    for (int i = index; i < book_count - 1; i++) {
        books[i] = books[i + 1];
    }
    book_count--;
    printf("Kitap başarıyla silindi!\n");
}

// Borrow a book
void borrow_book() {
    int id;
    printf("Ödünç vermek istediğiniz kitabın ID'sini girin: ");
    scanf("%d", &id);

    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            if (books[i].is_borrowed) {
                printf("Bu kitap zaten ödünç verilmiş.\n");
                return;
            }
            books[i].is_borrowed = 1;
            printf("Kitap başarıyla ödünç verildi!\n");
            return;
        }
    }
    printf("Bu ID'ye sahip bir kitap bulunamadı.\n");
}

// Return a book
void return_book() {
    int id;
    printf("İade etmek istediğiniz kitabın ID'sini girin: ");
    scanf("%d", &id);

    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            if (!books[i].is_borrowed) {
                printf("Bu kitap zaten mevcut durumda.\n");
                return;
            }
            books[i].is_borrowed = 0;
            printf("Kitap başarıyla iade alındı!\n");
            return;
        }
    }
    printf("Bu ID'ye sahip bir kitap bulunamadı.\n");
}

// Add a new member
void add_member() {
    if (member_count >= MAX_MEMBERS) {
        printf("Üye sınırına ulaşıldı!\n");
        return;
    }

    Member new_member;
    new_member.id = (member_count > 0) ? members[member_count - 1].id + 1 : 1;

    printf("Üye Adı: ");
    getchar();
    fgets(new_member.name, 100, stdin);
    new_member.name[strcspn(new_member.name, "\n")] = '\0';

    printf("E-posta: ");
    fgets(new_member.email, 100, stdin);
    new_member.email[strcspn(new_member.email, "\n")] = '\0';

    members[member_count++] = new_member;
    printf("Üye başarıyla eklendi!\n");
}

// List all members
void list_members() {
    if (member_count == 0) {
        printf("Henüz hiç üye eklenmemiş.\n");
        return;
    }

    printf("\n--- Üye Listesi ---\n");
    for (int i = 0; i < member_count; i++) {
        printf("ID: %d | İsim: %s | E-posta: %s\n", members[i].id, members[i].name, members[i].email);
    }
}

// Calculate late fee
void calculate_late_fee() {
    int id, days_late;
    printf("Geç iade edilen kitabın ID'sini girin: ");
    scanf("%d", &id);

    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            if (!books[i].is_borrowed) {
                printf("Bu kitap zaten mevcut.\n");
                return;
            }
            printf("Gecikme süresini (gün): ");
            scanf("%d", &days_late);

            int fee = days_late * 2; // Günlük gecikme ücreti 2 TL
            printf("Gecikme ücreti: %d TL\n", fee);
            return;
        }
    }
    printf("Bu ID'ye sahip bir kitap bulunamadı.\n");
}

// Menu
void menu() {
    int choice;
    do {
        printf("\n--- Akıllı Kütüphane Sistemi ---\n");
        printf("1. Kitap Ekle\n");
        printf("2. Kitapları Listele\n");
        printf("3. Kitap Sil\n");
        printf("4. Kitap Ödünç Ver\n");
        printf("5. Kitap İade Al\n");
        printf("6. Üye Ekle\n");
        printf("7. Üyeleri Listele\n");
        printf("8. Gecikme Ücreti Hesapla\n");
        printf("0. Çıkış\n");
        printf("Seçiminiz: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_book(); break;
            case 2: list_books(); break;
            case 3: delete_book(); break;
            case 4: borrow_book(); break;
            case 5: return_book(); break;
            case 6: add_member(); break;
            case 7: list_members(); break;
            case 8: calculate_late_fee(); break;
            case 0: printf("Çıkış yapılıyor...\n"); break;
            default: printf("Geçersiz seçim, tekrar deneyin.\n");
        }
    } while (choice != 0);
}
