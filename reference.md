Berikut adalah tabel panduan penggunaan memori yang paling tepat untuk implementasi **Dynamic Vector** Anda.

Pilihan ini didasarkan pada keseimbangan antara **keamanan** (menghindari bug nilai sampah) dan **fungsionalitas** (kebutuhan resize).

### Tabel Strategi Alokasi Memori Vector

| Fungsi | Penggunaan Terbaik dalam Vector | Alasan Utama | Contoh Kode |
| --- | --- | --- | --- |
| **`malloc`** | Membuat **"Wadah"** Vector (`struct Vector*`) di Heap. | Kita akan segera mengisi nilai properti struct (`size`, `capacity`) secara manual, jadi tidak perlu nol (0). `malloc` sedikit lebih cepat dari `calloc`. | `Vector* v = (Vector*)malloc(sizeof(Vector));` |
| **`calloc`** | Membuat **Array Data Awal** (`v->data`). | **Keamanan.** Mengisi array dengan `0` mencegah bug "nilai sampah" yang tadi menyebabkan error *AddressSanitizer*. Memudahkan debugging. | `v->data = (int*)calloc(initial_cap, sizeof(int));` |
| **`realloc`** | **Memperbesar Array** saat penuh (`push_back`). | Satu-satunya fungsi yang bisa memperbesar memori **tanpa menghapus data lama** yang sudah ada di dalamnya. | `v->data = (int*)realloc(v->data, new_cap * sizeof(int));` |

---

### Penjelasan Detail & Skenario

#### 1. Malloc: Untuk Struct-nya (Wadahnya)

Saat Anda membuat pointer `Vector* vec`, Anda hanya butuh blok memori mentah.

* **Kenapa tidak calloc?** Karena baris berikutnya Anda pasti menulis:
```c
vec->size = 0;
vec->capacity = 8;

```


Karena Anda langsung menimpanya dengan nilai pasti, membersihkan memori dengan `calloc` di sini adalah langkah mubazir (redundant).

#### 2. Calloc: Untuk Array Datanya (Isinya)

Saat `initialize` dipanggil, Anda menyiapkan array kosong.

* **Kenapa calloc?** Jika Anda menggunakan `malloc`, array tersebut berisi angka acak (misal: `-842150451`). Jika nanti Anda tidak sengaja mengakses indeks yang belum di-`push`, logika program Anda bisa kacau. Dengan `calloc`, isinya pasti `0`. Ini "jaring pengaman" yang baik.

#### 3. Realloc: Jantungnya Dynamic Array

Ini adalah fungsi paling krusial untuk Vector. Saat `size == capacity`, Anda harus memanggil `realloc`.

* **Cara kerja:** Ia mencari memori kosong di sebelah blok array Anda saat ini.
* Jika ada ruang: Array diperpanjang di tempat (sangat cepat).
* Jika tidak ada ruang: Ia mencari tempat baru yang muat, **menyalin** semua data lama ke tempat baru, lalu menghapus tempat lama otomatis.



---

### Contoh Implementasi Gabungan

Berikut adalah bagaimana ketiga fungsi tersebut bekerja sama dalam satu siklus hidup Vector:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int capacity;
    int* data;
} Vector;

// 1. MALLOC: Membuat Struct
Vector* create_vector() {
    Vector* v = (Vector*)malloc(sizeof(Vector)); 
    if (!v) return NULL;
    
    v->size = 0;
    v->capacity = 4; // Kapasitas awal
    
    // 2. CALLOC: Membuat Array Data Awal (Bersih 0)
    v->data = (int*)calloc(v->capacity, sizeof(int));
    if (!v->data) {
        free(v); // Gagal array, hapus struct
        return NULL;
    }
    
    return v;
}

void push_back(Vector* v, int value) {
    if (v->size == v->capacity) {
        // Logika pertumbuhan: Kali 2
        int new_capacity = v->capacity * 2;
        
        // 3. REALLOC: Resize saat penuh
        // PENTING: Tampung di pointer sementara dulu!
        int* temp = (int*)realloc(v->data, new_capacity * sizeof(int));
        
        if (temp == NULL) {
            printf("Gagal resize! Memori penuh.\n");
            return; // Data lama (v->data) masih aman
        }
        
        v->data = temp;
        v->capacity = new_capacity;
        printf("-> Vector membesar menjadi: %d\n", v->capacity);
    }
    
    v->data[v->size] = value;
    v->size++;
}

int main() {
    Vector* vec = create_vector();
    
    // Test resize
    for(int i=0; i<6; i++) {
        push_back(vec, i*10);
    }
    // Output nanti akan menunjukkan transisi realloc dari 4 ke 8
    
    return 0;
}

```
