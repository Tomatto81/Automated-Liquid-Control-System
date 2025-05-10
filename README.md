# Automated Liquid Process Control System (ATmega128)

## 📥 Cara Simulasi
### Opsi 1: Langsung di Proteus (Tanpa Kompilasi)
1. **Download** file `Firmware/ATMega_Process_Control.cof` dari repository ini.
2. Buka file `Schematic/ATMega_Process_Control.pdsprj` di Proteus.
3. **Double-click** ATmega128 di schematic:
   - Pilih `ATMega_Process_Control.cof` sebagai **Program File**.
   - Atur clock speed ke **10MHz** (sesuai desain).
4. Jalankan simulasi dengan tombol **Play**.

### Opsi 2: Modifikasi & Kompilasi Ulang
Jika ingin mengubah kode:
1. Edit file `Firmware/ATMega_Process_Control.c` sesuai kebutuhan.
2. **Compile dengan CodeVisionAVR** (CVAVR):
   - Buat project baru di CVAVR, tambahkan `ATMega_Process_Control.c`.
   - Set konfigurasi: **ATmega128**, **10MHz**.
   - Generate file `.cof` (pilih opsi *COFF Debug File* di compiler).
3. Gunakan file `.cof` hasil compile di Proteus (langkah Opsi 1).

## 📂 Struktur File
Firmware/
├── ATMega_Process_Control.c # Source code utama (bisa dibaca/dimodifikasi)
└── ATMega_Process_Control.cof # File COF siap simulasi (pre-compiled)

Schematic/
└── ATMega_Process_Control.pdsprj # Desain rangkaian Proteus

## ⚠️ Catatan Penting
- File `.cof` sudah di-generate dengan **CodeVisionAVR** dan kompatibel dengan **Proteus 8+**.
- Jika simulasi error:
  - Pastikan **clock speed** di Proteus sama dengan kode (10MHz).
  - Cek **path file `.cof`** di schematic (harus mengarah ke file yang benar).
- Untuk kompilasi, Anda **memerlukan CodeVisionAVR** (file `.prj` tidak disertakan).

## ✉️ Kontak
Ammar Shidqi Matotorang  
[email](ammarshidqi46@gmail.com) | [Linkedin](https://www.linkedin.com/in/ammar-shidqi-mattotorang-3bb152173/)
