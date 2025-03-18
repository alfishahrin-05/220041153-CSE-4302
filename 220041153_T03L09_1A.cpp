#include <iostream>
using namespace std;

class Artwork {
protected:
    string title;
    string artist;
    double price;
    double discount = 0; 

public:
    Artwork(string t, string a, double p) : title(t), artist(a), price(p) {}

    virtual ~Artwork() {}

    virtual void displayDetails() {
        cout << "Title of the artwork: " << title << endl;
        cout << "Name of the artist: " << artist << endl;
        cout << "Price of the art: " << price << endl;
        if (discount > 0) {
            double finalPrice = price - (price * (discount / 100));
            cout << "Initial Price: " << price << endl;
            cout << "Final Price after discount: " << finalPrice << endl;
        } else {
            cout << "Discount is not available" << endl;
        }
    }

    virtual void applyDiscount(double percentage) {
        discount = percentage; 
    }
};

class Painting : public Artwork {
private:
    string medium;

public:
    Painting(string t, string a, double p, string m) : Artwork(t, a, p), medium(m) {}

    void displayDetails() override {
        Artwork::displayDetails();
        cout << "Medium of the art: " << medium << endl;
    }
};

class Sculpture : public Artwork {
private:
    string material;

public:
    Sculpture(string t, string a, double p, string ml) : Artwork(t, a, p), material(ml) {}

    void applyDiscount(double percentage) override {

    }

    void displayDetails() override {
        Artwork::displayDetails();
        cout << "Material of the art: " << material << endl;
    }
};

class DigitalArt : public Artwork {
private:
    string resolution;

public:
    DigitalArt(string t, string a, double p, string r) : Artwork(t, a, p), resolution(r) {}

    void displayDetails() override {
        Artwork::displayDetails();
        cout << "Resolution of the art: " << resolution << endl;
    }
};

void displayGalleryDetails(Artwork** gallery,int size)
{
    for(int i=0;i<size;i++)
    {
        gallery[i]->displayDetails();
    }
}

int main() {
    Artwork* arts[3];
    arts[0] = new Painting("Painting 1", "Person 1", 10000, "Acrylic");
    arts[1] = new Sculpture("Sculpture 1", "Person 2", 100000, "Bronze");
    arts[2] = new DigitalArt("NFT1", "Unknown", 100000, "800x600");

    for (int i = 0; i < 3; i++) {
        arts[i]->applyDiscount(5);
        arts[i]->displayDetails();
        cout << endl; 
    }
    return 0;
    displayGalleryDetails(arts,3);
}
