# Acil Servis Hasta Takip Programı

Bu C programı, acil servislerde hasta bilgilerini saklamak, triage (öncelik sıralaması) yapmak ve hasta verilerini yönetmek için kullanılabilir. Program, hasta bilgilerini kullanıcıdan alır, her hasta için bir öncelik sıralaması yapar ve bu bilgileri bir bağlı liste olarak saklar.

## Özellikler

- **Hasta Ekleme**: Kullanıcı, hasta bilgilerini (ad, soyad, TC Kimlik No, yaş, cinsiyet, şikayet, tansiyon, ateş gibi) girebilir ve program bu verileri ilgili yapıda saklar.
- **Triage Değerlendirmesi**: Şikayetlere göre her hasta için bir öncelik derecesi belirlenir. Örneğin, kalp krizi ve nefes darlığı gibi durumlar kritik olarak değerlendirilir.
- **Ateş ve Tansiyon Derecelendirmesi**: Hasta ateşi ve tansiyonu belirli aralıklara göre derecelendirilir (normal, yüksek, düşük).
- **Reçete Numarası**: Her hasta için rastgele bir reçete numarası oluşturulur.
- **Hasta Listeleme**: Program, eklenen hastaların bilgilerini sırasıyla yazdırır.

## Kullanım

1. **Hasta Bilgilerini Girme**: Program çalıştırıldığında, kullanıcıdan sırasıyla aşağıdaki bilgiler istenecektir:
    - Ad, Soyad, TC Kimlik No
    - Yaş, Cinsiyet
    - Şikayet
    - Adres, Telefon Numarası
    - Alerji Durumu
    - Tansiyon Değerleri (Büyük ve Küçük)
    - Ateş

2. **Triage (Öncelik) Değerlendirmesi**: Hasta şikayeti değerlendirildikten sonra, bir öncelik (1: Kritik, 2: Öncelikli, 3: Normal) atanır. Kritik durumdaki hastalar önce gelir.

3. **Yeni Hasta Ekleme**: Bir hasta bilgisi girdikten sonra, kullanıcı başka bir hasta eklemek isteyip istemediği sorulur. Eğer evet derse, yeni hasta bilgileri alınır. Eğer hayır derse, program hastaların listesini gösterir.

4. **Hasta Listeleme**: Program, hasta ekleme işlemi tamamlandıktan sonra, acil servisteki tüm hasta bilgilerini yazdırır.

## Kod Yapısı

- **`Hasta` Yapısı**: Hasta bilgileri bu yapı içinde saklanır. Bu yapı aşağıdaki alanlara sahiptir:
  - Ad, Soyad, TC Kimlik No, Yaş, Cinsiyet
  - Şikayet, Öncelik, Reçete No
  - Adres, Telefon Numarası, Alerji
  - Tansiyon (Büyük/Küçük), Ateş, Ateş Derecesi, Tansiyon Derecesi
  - `sonraki`: Bir sonraki hastaya işaret eden bağlantı (bağlı liste)
  
- **Bağlı Liste**: Hastalar bir bağlı liste yapısında saklanır. Her hasta, bir sonraki hastayı işaret eder.



