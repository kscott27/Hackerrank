#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

void counterspell(Spell *spell) {

  /* Enter your code here */
    if( dynamic_cast<Fireball*>(spell) != NULL ) {
        Fireball* fireball = dynamic_cast<Fireball*>(spell);
        fireball->revealFirepower();
    } else if( dynamic_cast<Frostbite*>(spell) != NULL ) {
        Frostbite* frostbite = dynamic_cast<Frostbite*>(spell);
        frostbite->revealFrostpower();
    } else if( dynamic_cast<Thunderstorm*>(spell) != NULL ) {
        Thunderstorm* thunderstorm = dynamic_cast<Thunderstorm*>(spell);
        thunderstorm->revealThunderpower();
    } else if( dynamic_cast<Waterbolt*>(spell) != NULL ) {
        Waterbolt* waterbolt = dynamic_cast<Waterbolt*>(spell);
        waterbolt->revealWaterpower();
    } else {
        string scrollName = spell->revealScrollName();

        size_t scrollLength = scrollName.length();
        size_t journalLength = SpellJournal::journal.length();
        long matrix[scrollLength+1][journalLength+1] = {0};

        // For some reason, the matrix was not getting initialized to 0
        // for subsequent runs. This implementation resolved that...
        for( size_t j = 0; j <= scrollLength; j++ ) {
            for( size_t i = 0; i <= journalLength; i++ ) {
                matrix[j][i] = 0;
            }
        }

        for( size_t j = 0; j < scrollLength; j++ ) {
            for( size_t i = 0; i < journalLength; i++ ) {
                // cout << "i = " << i << " j = " << j << endl;
                if( scrollName[j] != SpellJournal::journal[i] ) {
                    size_t upper = matrix[j][i+1];
                    size_t left  = matrix[j+1][i];
                    if( upper > left ) {
                        // cout << upper << endl;
                        matrix[j+1][i+1] = upper;
                    } else {
                        // cout << left << endl;
                        matrix[j+1][i+1] = left;
                    }
                } else {
                    // cout << matrix[j][i] + 1 << endl;
                    matrix[j+1][i+1] = matrix[j][i] + 1;
                }
            }
            // cout << endl;
        }

        cout << matrix[scrollLength][journalLength] << endl;
    }
}

class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            } 
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}