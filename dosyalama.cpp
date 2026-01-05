#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


using namespace std;

struct Hediye{
    string ad;
    string marka;
    int fiyat;
    int uretim;
};

void HediyeEkle();
void HediyeListele();
void HediyeAra();
void HediyeSil();
void HediyeDuzenle();

int main() {
    char anamenu;
    do {
        system("cls");
        
        cout << "|-------Hosgeldiniz------|" << endl;
        cout << "|      Secim Yapiniz     |" << endl;
        cout << "|   1- Hediye Ekleme     |" << endl;
        cout << "|   2- Hediye Listeleme  |" << endl;
        cout << "|   3- Hediye Arama      |" << endl;
        cout << "|   4- Hediye Sil        |" << endl;
        cout << "|   5- Hediye Duzenle    |" << endl;
        cout << "|------------------------|" << endl;

        char secim;
        cout << "Lütfen Seçim yapiniz." << endl;
        cin >> secim; 

        switch (secim)
        {
        case '1': HediyeEkle(); break;
        case '2': HediyeListele(); break;
        case '3': HediyeAra(); break;
        case '4': HediyeSil(); break;
        case '5': HediyeDuzenle(); break;
        default: cout << "Gecersiz secim!" << endl; break;
        }

        cout << "\nAna menuye donmek ister misiniz? (e/h): ";
        cin >> anamenu;
       
    } while (anamenu == 'e' || anamenu == 'E');

    return 0;
}

void HediyeEkle()
{
    ofstream yaz("hediye.txt", ios::app);
    char secim;
    int adet = 0;
    Hediye hdy;

    do {
        cout << "Hediye Adi Giriniz: ";
        getline(cin, hdy.ad);
        cout << "Hediye Markasi Giriniz: ";
        getline(cin, hdy.marka);
        cout << "Hediye Fiyati Giriniz: ";
        cin >> hdy.fiyat;
        cout << "Hediye Uretim Tarihini Giriniz: ";
        cin >> hdy.uretim;

        yaz << hdy.ad << endl;
        yaz << hdy.marka << endl;
        yaz << hdy.fiyat << endl;
        yaz << hdy.uretim << endl;

        adet++;
        cout << "Baska kayit eklemek istiyor musunuz? (e/h): ";
        cin >> secim;
    } while (secim == 'e' || secim == 'E');

    cout << adet << " adet hediye eklendi." << endl;
    yaz.close();
}

void HediyeListele()
{
    ifstream oku("hediye.txt");
    if (!oku) { cout << "Dosya acilamadi!" << endl; return; }

    Hediye hdy;
    int sayac = 0;

    while (getline(oku, hdy.ad))
    {
        getline(oku, hdy.marka);
        oku >> hdy.fiyat >> hdy.uretim;
        oku.ignore();

        sayac++;
        cout << sayac << ". Hediyenin Bilgileri" << endl;
        cout << "Adi    : " << hdy.ad << endl;
        cout << "Markasi: " << hdy.marka << endl;
        cout << "Fiyati : " << hdy.fiyat << endl;
        cout << "Uretim : " << hdy.uretim << endl;
        cout << "*******************************" << endl;
    }

    if (sayac == 0)
        cout << "Kayit bulunamadi." << endl;
    else
        cout << "Toplam hediye sayisi: " << sayac << endl;

    oku.close();
}

void HediyeAra()
{
    ifstream oku("hediye.txt");
    if (!oku) { cout << "Dosya acilamadi!" << endl; return; }

    string aranan;
    cout << "Aranan hediye adini giriniz: ";
    cin.ignore();
    getline(cin, aranan);

    Hediye hdy;
    bool bulundu = false;
    while (getline(oku, hdy.ad))
    {
        getline(oku, hdy.marka);
        oku >> hdy.fiyat >> hdy.uretim;
        oku.ignore();

        if (hdy.ad == aranan)
        {
            cout << "Bulunan Hediyenin Bilgileri" << endl;
            cout << "Adi    : " << hdy.ad << endl;
            cout << "Markasi: " << hdy.marka << endl;
            cout << "Fiyati : " << hdy.fiyat << endl;
            cout << "Uretim : " << hdy.uretim << endl;
            bulundu = true;
            break;
        }
    }

    if (!bulundu) cout << "Kayit Bulunamadi." << endl;

    oku.close();
}
void HediyeSil()
{
    ifstream oku("hediye.txt");
    ofstream gecici("gecici.txt");

    if (!oku || !gecici) {
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    string silinen;
    cout << "Silinecek hediye adini giriniz: ";
    cin.ignore();
    getline(cin, silinen);

    Hediye hdy;
    bool bulundu = false;

    while (getline(oku, hdy.ad))
    {
        getline(oku, hdy.marka);
        oku >> hdy.fiyat >> hdy.uretim;
        oku.ignore();

        if (hdy.ad == silinen)
        {
            bulundu = true;
            continue; 
        }

        gecici << hdy.ad << endl;
        gecici << hdy.marka << endl;
        gecici << hdy.fiyat << endl;
        gecici << hdy.uretim << endl;
    }

    oku.close();
    gecici.close();

    remove("hediye.txt");
    rename("gecici.txt", "hediye.txt");

    if (bulundu) cout << "Kayit silindi." << endl;
    else cout << "Kayit bulunamadi." << endl;
}

void HediyeDuzenle()
{
    ifstream oku("hediye.txt");
    ofstream gecici("gecici.txt");

    if (!oku || !gecici) {
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    string aranan;
    cout << "Duzenlenecek hediye adini giriniz: ";
    cin.ignore();
    getline(cin, aranan);

    Hediye hdy;
    bool bulundu = false;

    while (getline(oku, hdy.ad))
    {
        getline(oku, hdy.marka);
        oku >> hdy.fiyat >> hdy.uretim;
        oku.ignore();

        if (hdy.ad == aranan)
        {
            cout << "Yeni Hediye Adi: ";
            getline(cin, hdy.ad);
            cout << "Yeni Hediye Markasi: ";
            getline(cin, hdy.marka);
            cout << "Yeni Hediye Fiyati: ";
            cin >> hdy.fiyat;
            cout << "Yeni Uretim Tarihi: ";
            cin >> hdy.uretim;
            cin.ignore();
            bulundu = true;
        }

        gecici << hdy.ad << endl;
        gecici << hdy.marka << endl;
        gecici << hdy.fiyat << endl;
        gecici << hdy.uretim << endl;
    }

    oku.close();
    gecici.close();

    remove("hediye.txt");
    rename("gecici.txt", "hediye.txt");

    if (bulundu) cout << "Kayit duzenlendi." << endl;
    else cout << "Kayit bulunamadi." << endl;
}
