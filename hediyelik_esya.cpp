#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

struct Hediye
{
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
        cin.ignore();

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
        cin.ignore();
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
        cin.ignore();
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

    vector<Hediye> hediyeler;
    Hediye hdy;
    while (getline(oku, hdy.ad))
    {
        getline(oku, hdy.marka);
        oku >> hdy.fiyat >> hdy.uretim;
        oku.ignore();
        hediyeler.push_back(hdy);
    }

    cout << "Toplam hediye kayit sayisi: " << hediyeler.size() << endl;

    for (int i = 0; i < hediyeler.size(); i++)
    {
        cout << i + 1 << ". Hediyenin Bilgileri" << endl;
        cout << "Adi    : " << hediyeler[i].ad << endl;
        cout << "Markasi: " << hediyeler[i].marka << endl;
        cout << "Fiyati : " << hediyeler[i].fiyat << endl;
        cout << "Uretim : " << hediyeler[i].uretim << endl;
        cout << "*******************************" << endl;
    }

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
    if (!oku) { cout << "Dosya acilamadi!" << endl; return; }

    string silinen;
    cout << "Silmek istediginiz hediye adini giriniz: ";
    cin.ignore();
    getline(cin, silinen);

    vector<Hediye> hediyeler;
    Hediye hdy;
    bool bulundu = false;

    while (getline(oku, hdy.ad))
    {
        getline(oku, hdy.marka);
        oku >> hdy.fiyat >> hdy.uretim;
        oku.ignore();

        if (hdy.ad == silinen)
        {
            cout << "Hediye bulundu: " << hdy.ad << endl;
            cout << "Silinsin mi? (e/h): ";
            char secim;
            cin >> secim;
            if (secim == 'e' || secim == 'E')
            {
                bulundu = true;
                continue; // Silmek için ekleme
            }
        }
        hediyeler.push_back(hdy);
    }

    oku.close();

    ofstream yaz("hediye.txt");
    for (auto& h : hediyeler)
    {
        yaz << h.ad << endl;
        yaz << h.marka << endl;
        yaz << h.fiyat << endl;
        yaz << h.uretim << endl;
    }
    yaz.close();

    if (bulundu) cout << "Kayit silindi." << endl;
    else cout << "Kayit bulunamadi." << endl;
}

void HediyeDuzenle()
{
    ifstream oku("hediye.txt");
    if (!oku) { cout << "Dosya acilamadi!" << endl; return; }

    string aranan;
    cout << "Duzenlemek istediginiz hediye adini giriniz: ";
    cin.ignore();
    getline(cin, aranan);

    vector<Hediye> hediyeler;
    Hediye hdy;
    bool bulundu = false;

    while (getline(oku, hdy.ad))
    {
        getline(oku, hdy.marka);
        oku >> hdy.fiyat >> hdy.uretim;
        oku.ignore();

        if (hdy.ad == aranan)
        {
            cout << "Hediye bulundu: " << hdy.ad << endl;
            cout << "Duzenlemek istiyor musunuz? (e/h): ";
            char secim;
            cin >> secim;
            cin.ignore();
            if (secim == 'e' || secim == 'E')
            {
                cout << "Yeni Hediye Adi: "; getline(cin, hdy.ad);
                cout << "Yeni Hediye Markasi: "; getline(cin, hdy.marka);
                cout << "Yeni Hediye Fiyati: "; cin >> hdy.fiyat;
                cout << "Yeni Uretim Tarihi: "; cin >> hdy.uretim;
                cin.ignore();
                bulundu = true;
            }
        }
        hediyeler.push_back(hdy);
    }

    oku.close();

    ofstream yaz("hediye.txt");
    for (auto& h : hediyeler)
    {
        yaz << h.ad << endl;
        yaz << h.marka << endl;
        yaz << h.fiyat << endl;
        yaz << h.uretim << endl;
    }
    yaz.close();

    if (bulundu) cout << "Kayit duzeltilidi." << endl;
    else cout << "Kayit bulunamadi." << endl;
}
