# Kütüphane Yönetim Sistemi

Bu proje, C programlama dili kullanılarak geliştirilmiş bir **Kütüphane Yönetim Sistemi** uygulamasıdır. Program, kütüphanedeki kitap ve üyeleri yönetmek için gerekli temel işlevleri sağlar. Ayrıca dosya tabanlı veri saklama özelliği ile bilgileri kalıcı olarak depolar.

## Özellikler

- **Kitap İşlemleri:**
  - Kitap ekleme
  - Kitap listeleme
  - Kitap silme
  - Kitap ödünç verme ve iade alma

- **Üye İşlemleri:**
  - Üye ekleme
  - Üyeleri listeleme

- **Diğer Özellikler:**
  - Gecikme ücreti hesaplama
  - Kitap ve üye bilgilerinin dosyadan yüklenmesi ve kaydedilmesi

## Kullanılan Dosyalar

- **`books.txt`**: Kitap bilgileri bu dosyada saklanır.
- **`members.txt`**: Üye bilgileri bu dosyada saklanır.

## Kurulum

1. **Kaynak Kodunu İndirin**  
   Bu projeyi GitHub veya başka bir kaynaktan indirerek cihazınıza yükleyin.

2. **Derleme**  
   Bir C derleyicisi kullanarak aşağıdaki komutla projeyi derleyin:
   gcc library_management.c -o library_management
