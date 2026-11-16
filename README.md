# Proyek-Array-C-C2583207023

Sistem Monitoring Stok dan Penjualan Kantin Kampus

Nama: Aldi Kurniawan

NIM: C2583207023

Kelas: PTI 3A

Mata Kuliah: Algoritma dan Pemrograman Lanjutan

Dosen Pengampu: Taofik Muhammad, M.Kom

Deskripsi
Aplikasi console berbasis bahasa C untuk mengelola produk kantin, memproses transaksi pembelian beberapa produk, memperbarui stok, melakukan pencarian dan pengurutan, serta menampilkan laporan penjualan. Data disimpan di memori selama program berjalan; program tidak menggunakan database atau file eksternal.
Fitur
1. Menampilkan seluruh produk beserta harga, stok, dan jumlah terjual.
2. Menambahkan produk baru (maksimal 50 produk).
3. Mengubah nama, harga, dan/atau stok produk.
4. Memproses satu transaksi yang dapat berisi beberapa jenis produk.
5. Menambah stok produk.
6. Mencari produk berdasarkan nama (tidak membedakan huruf besar/kecil).
7. Mengurutkan produk berdasarkan harga termurah atau jumlah terjual terbanyak.
8. Menampilkan jumlah setiap produk yang terjual, total unit, total pendapatan, dan produk terlaris.
9. Menampilkan produk yang stoknya kurang dari 5.
Penerapan Array
- nama[MAX_PRODUK][PANJANG_NAMA]: array karakter dua dimensi untuk nama produk.
- harga[MAX_PRODUK]: array satu dimensi untuk harga produk.
- stok[MAX_PRODUK]: array satu dimensi untuk stok tersedia.
- terjual[MAX_PRODUK]: array satu dimensi untuk jumlah unit yang telah terjual.
- pendapatanProduk[MAX_PRODUK]: array satu dimensi untuk mencatat pendapatan tiap produk berdasarkan harga ketika transaksi terjadi.
- jumlahBeli[MAX_PRODUK]: array sementara untuk menampung jumlah produk dalam satu transaksi.
- Kapasitas maksimal 50 produk dan tersedia 5 produk awal.
Indeks setiap array yang berkaitan selalu merujuk pada produk yang sama. Ketika pengurutan dilakukan, seluruh data pada indeks terkait ikut ditukar agar nama, harga, stok, jumlah terjual, dan pendapatan tidak tertukar.
Algoritma dan Validasi
- Menu utama menggunakan do-while dan switch.
- Pengulangan daftar produk dan transaksi menggunakan for/`while`.
- Pencarian nama dilakukan dengan pencarian linear.
- Pengurutan menggunakan Bubble Sort.
- Transaksi menampung jumlah pembelian pada array sementara. Stok dan jumlah terjual baru diperbarui setelah pengguna menyelesaikan input transaksi. Pembelian yang melampaui stok ditolak.
- Input menu, nomor produk, jumlah pembelian, harga, dan stok diperiksa. Nilai harga/stok negatif ditolak; jumlah pembelian harus lebih dari nol; kapasitas produk dibatasi 50.
- Pendapatan dicatat pada saat transaksi sehingga perubahan harga setelah penjualan tidak mengubah catatan pendapatan transaksi sebelumnya.
Cara Kompilasi dan Menjalankan
Pastikan GCC atau compiler C tersedia.
Linux / macOS
gcc -std=c99 -Wall -Wextra -pedantic kantin.c -o kantin
./kantin
Windows (MinGW GCC)
gcc -std=c99 -Wall -Wextra -pedantic kantin.c -o kantin.exe
kantin.exe
Program dimulai dengan 5 produk awal. Pilih menu sesuai kebutuhan. Pada menu transaksi, masukkan nomor produk dan jumlah pembelian; masukkan 0 pada nomor produk untuk menyelesaikan transaksi.
Data Produk Awal
No.	Produk	Harga (Rp)	Stok awal
1	Nasi Goreng	15.000	20
2	Mie Goreng	12.000	15
3	Air Mineral	5.000	40
4	Es Teh	5.000	30
5	Roti Cokelat	7.000	18


Rencana dan Hasil Pengujian
Jalankan setiap skenario berikut dan simpan tangkapan layar terminal sebagai bukti. Screenshot perlu dibuat dari komputer pengguna setelah program dijalankan; tabel ini bukan pengganti bukti screenshot.
No.	Skenario	Input/tindakan pengujian	Hasil yang diharapkan

1	Tambah produk	Pilih menu 2, masukkan Pisang, harga 6000, stok 10; lalu menu 1	Produk Pisang tampil pada daftar dengan harga dan stok yang dimasukkan.

2	Transaksi beberapa produk	Menu 4; produk 1 sebanyak 2 unit; produk 3 sebanyak 1 unit; masukkan 0	Struk menampilkan Nasi Goreng Rp30.000 dan Air Mineral Rp5.000; total Rp35.000.

3	Pembaruan stok	Setelah skenario 2, pilih menu 1	Stok Nasi Goreng menjadi 18 dan Air Mineral menjadi 39; jumlah terjual masing-masing bertambah.

4	Stok tidak cukup	Menu 4; pilih produk 1 dengan jumlah melebihi stok tersedia	Pembelian ditolak untuk item tersebut dan stok tidak berkurang akibat input yang ditolak.

5	Laporan	Pilih menu 8 setelah transaksi	Total unit, pendapatan, jumlah terjual tiap produk, dan produk terlaris sesuai transaksi yang berhasil.

6	Pengurutan	Menu 7, pilih 1; ulangi menu 7 pilih 2	Daftar terurut dari harga termurah dan dari jumlah terjual terbanyak.

7	Pencarian dan stok	Menu 6 cari Es Teh; menu 9 untuk stok menipis	Informasi produk ditemukan; menu stok menipis menampilkan produk dengan stok kurang dari 5 atau pesan jika tidak ada.


Tambahan pengujian validasi: coba pilihan menu di luar 0–9, nomor produk yang tidak tersedia, jumlah pembelian 0/negatif, harga atau stok negatif saat menambah/mengubah produk, nama produk yang sudah ada, serta penambahan ketika jumlah produk sudah mencapai 50. Pastikan program menampilkan pesan yang sesuai.

Daftar Produk

<img width="489" height="392" alt="image" src="https://github.com/user-attachments/assets/6d9e0136-3059-4ef1-b455-0a703edda9bf" />

Tambah Produk

<img width="389" height="286" alt="image" src="https://github.com/user-attachments/assets/148c4bd3-7287-42b4-b28b-e84fa3c0a271" />

Transaksi

<img width="499" height="454" alt="image" src="https://github.com/user-attachments/assets/b5121253-9dfb-4c7d-9ff4-800692c0f497" />

Pembaruan stok

<img width="484" height="404" alt="image" src="https://github.com/user-attachments/assets/3c335ed4-f56c-4150-a1fd-847973135248" />

stok tidak cukup

<img width="488" height="234" alt="image" src="https://github.com/user-attachments/assets/c4bc5843-1d69-49c2-bf3b-6bafbec46baf" />

laporan

<img width="559" height="420" alt="image" src="https://github.com/user-attachments/assets/eb75fa5f-7a06-4e4c-ba8f-80f00357de0d" />

pengurutan

<img width="480" height="437" alt="image" src="https://github.com/user-attachments/assets/3088afbc-f41b-4b35-bac8-5d401e4d4287" />

pencarian stok menipis

<img width="409" height="266" alt="image" src="https://github.com/user-attachments/assets/f531e7a8-2acc-4943-a35d-037ff01a177c" />
