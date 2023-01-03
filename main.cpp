#include <iostream>
#include <random> // biblioteka losujaca
#include <fstream> // stream wejsciowy i wyjsciowy
#include <filesystem> // quailty-of-life, w celu ulatwienia wczytywania i zapisu gry
#include <windows.h> // quailty-of-life, w celu ulatwienia wczytywania i zapisu gry
#include <Lmcons.h> // quailty-of-life, w celu ulatwienia wczytywania i zapisu gry

using namespace std;


enum Element {
    water = 0, earth, air, fire, ice, steel
};

const char *element_name[] = {"WODA", "ZIEMIA", "POWIETRZE", "OGIEN", "LOD", "STAL"};

enum Difficulty {
    easy = 0, medium = 1, hard = 2
};

string Names[] = {"Kaczucha", "Pletwacz", "Deszczownik", "Grabarz", "Pnaczak", "Wicherek", "Szumowir",
                  "Ogniopluj",
                  "Zarowor", "Magmozaur", "Sopelek", "Sniezynka", "Szronek", "Stalomiot", "Gwiazdostal"};

class Special {
private:
    string name;
    Element element;
    int usage_number;
    double points;
    int tours;
public:
    void setUsageNumber(int usageNumber) {
        usage_number = usageNumber;
    }

    const string &getName() const {
        return name;
    }

    Element getElement() const {
        return element;
    }

    int getUsageNumber() const {
        return usage_number;
    }

    double getPoints() const {
        return points;
    }

    int getTours() const {
        return tours;
    }

    Special(const string &name, Element element, int usage_number, double points, int tours) {
        this->name = name;
        this->element = element;
        this->usage_number = usage_number;
        this->points = points;
        this->tours = tours;
    }

    Special() {};
};

class PokeMonster {
private:
    Element element;
    string name;
    int power;
    int agility;
    int health;
    Special *special;
    int exp_when_kill;
    int curr_exp;
    int exp_to_evolve;
    bool is_dead;
    bool is_stunned;
    bool is_vulnerable;
    bool is_armored;
public:
    PokeMonster() {
        curr_exp = 0;
        is_dead = false;
        is_stunned = false;
        is_armored = false;
        is_vulnerable = true;

    };


    Element getElement() const {
        return element;
    }

    bool isStunned() const {
        return is_stunned;
    }

    void setIsStunned(bool isStunned) {
        is_stunned = isStunned;
    }

    bool isVulnerable() const {
        return is_vulnerable;
    }

    void setIsVulnerable(bool isVulnerable) {
        is_vulnerable = isVulnerable;
    }

    bool isArmored() const {
        return is_armored;
    }

    void setIsArmored(bool isArmored) {
        is_armored = isArmored;
    }

    void setElement(Element element) {
        this->element = element;
    }

    const string &getName() const {
        return name;
    }

    void setName(string &name) {
        PokeMonster::name = name;
    }

    int getPower() const {
        return power;
    }

    void setPower(int power) {
        PokeMonster::power = power;
    }

    int getAgility() const {
        return agility;
    }

    void setAgility(int agility) {
        PokeMonster::agility = agility;
    }

    int getHealth() const {
        return health;
    }

    void setHealth(int health) {
        PokeMonster::health = health;
    }

    Special *getSpecial() {
        return special;
    }

    void setSpecial(Special *special) {
        PokeMonster::special = special;
    }

    int getExpWhenKill() const {
        return exp_when_kill;
    }

    void setExpWhenKill(int expWhenKill) {
        exp_when_kill = expWhenKill;
    }

    int getCurrExp() const {
        return curr_exp;
    }

    void setCurrExp(int currExp) {
        curr_exp = currExp;
    }

    int getExpToEvolve() const {
        return exp_to_evolve;
    }

    void setExpToEvolve(int expToEvolve) {
        exp_to_evolve = expToEvolve;
    }

    bool isDead() const {
        return is_dead;
    }

    void setIsDead(bool isDead) {
        is_dead = isDead;
    }

    friend ostream &operator<<(ostream &os, const PokeMonster &monster);
};

class Enemy {
private:
    string name;
    PokeMonster monsters[6];
    bool is_dead = false;

public:
    const string &getName() const {
        return name;
    }

    PokeMonster *getMonsters() {
        return monsters;
    }

    void setName(const string &name) {
        Enemy::name = name;
    }

    Enemy(string name, PokeMonster *monsters, Difficulty difficulty) {
        this->name = name;
        int selected[6] = {15, 15, 15, 15};
        random_device rd;
        default_random_engine gen(rd()); //generator z biblioteki <random>
        uniform_int_distribution<> dist(0, 14);
        int rand = dist(gen);
        for (int i = 0; i < 4 + difficulty; i++) {
            [&]() {
                for (int j = 0; j < 4 + difficulty; j++) {
                    while (selected[j] == rand) {
                        rand = dist(gen);
                        j = 0;
                    }
                }
            }();
            selected[i] = rand;
            this->monsters[i] = monsters[rand];
            this->monsters[i].setPower(this->monsters[i].getPower());
            this->monsters[i].setHealth(this->monsters[i].getHealth());
        }

    }

    Enemy() {}

    bool isDead() const {
        return is_dead;
    }

    void setIsDead(bool isDead) {
        is_dead = isDead;
    }
};

class Effect {
private:
    string name;
    int tour;
    double points;
    PokeMonster *monster_caster;
    PokeMonster *monster_targert;

public:
    Effect() {}

    int getTour() const {
        return tour;
    }

    void setTour(int tour) {
        Effect::tour = tour;
    }

    int getPoints() const {
        return points;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Effect::name = name;
    }

    void setPoints(double points) {
        Effect::points = points;
    }

    PokeMonster *getMonsterCaster() {
        return monster_caster;
    }

    void setMonsterCaster(PokeMonster *monsterCaster) {
        monster_caster = monsterCaster;
    }

    PokeMonster *getMonsterTargert() {
        return monster_targert;
    }

    void setMonsterTargert(PokeMonster *monsterTargert) {
        monster_targert = monsterTargert;
    }
};

// tworzy stworzenia przy wyborze nowej gry
void Generator(PokeMonster *monsters, Special *special) {
    random_device rd;
    default_random_engine gen(rd()); //generator z biblioteki <random>
    uniform_int_distribution<> dist_pow(2, 7);
    uniform_int_distribution<> dist_ag(0, 10);
    uniform_int_distribution<> dist_exp_get(3, 8);
    uniform_int_distribution<> dist_exp_evolve(10, 15);
    for (int i = 0; i < 15; i++) {
        monsters[i].setName(Names[i]);
        if (i < 3) { monsters[i].setElement(water); }
        else if (i < 5) { monsters[i].setElement(earth); }
        else if (i < 7) { monsters[i].setElement(air); }
        else if (i < 10) { monsters[i].setElement(fire); }
        else if (i < 13) { monsters[i].setElement(ice); }
        else { monsters[i].setElement(steel); }
        if (monsters[i].getElement() == water) {
            uniform_int_distribution<> dist(0, 1);
            int n = dist(gen);
            monsters[i].setSpecial(
                    new Special(special[n].getName(), special[n].getElement(), special[n].getUsageNumber(),
                                special[n].getPoints(), special[n].getTours()));
        }
        if (monsters[i].getElement() == earth) {
            uniform_int_distribution<> dist(2, 3);
            int n = dist(gen);
            monsters[i].setSpecial(
                    new Special(special[n].getName(), special[n].getElement(), special[n].getUsageNumber(),
                                special[n].getPoints(), special[n].getTours()));
        }
        if (monsters[i].getElement() == air) {
            uniform_int_distribution<> dist(4, 5);
            int n = dist(gen);
            monsters[i].setSpecial(
                    new Special(special[n].getName(), special[n].getElement(), special[n].getUsageNumber(),
                                special[n].getPoints(), special[n].getTours()));
        }
        if (monsters[i].getElement() == fire) {
            uniform_int_distribution<> dist(6, 7);
            int n = dist(gen);
            monsters[i].setSpecial(
                    new Special(special[n].getName(), special[n].getElement(), special[n].getUsageNumber(),
                                special[n].getPoints(), special[n].getTours()));
        }
        if (monsters[i].getElement() == ice) {
            uniform_int_distribution<> dist(8, 9);
            int n = dist(gen);
            monsters[i].setSpecial(
                    new Special(special[n].getName(), special[n].getElement(), special[n].getUsageNumber(),
                                special[n].getPoints(), special[n].getTours()));
        }
        if (monsters[i].getElement() == steel) {
            uniform_int_distribution<> dist(10, 11);
            int n = dist(gen);
            monsters[i].setSpecial(
                    new Special(special[n].getName(), special[n].getElement(), special[n].getUsageNumber(),
                                special[n].getPoints(), special[n].getTours()));
        }
        monsters[i].setPower(dist_pow(gen));
        monsters[i].setAgility(dist_ag(gen));
        // lacznie statystyki (AGI + POW) nie moga przekroczyc 40 w momencie generowania, balans punktow
        monsters[i].setHealth(40 - monsters[i].getAgility() - monsters[i].getPower());
        monsters[i].setExpWhenKill(dist_exp_get(gen));
        monsters[i].setExpToEvolve(dist_exp_evolve(gen));
    }
};

// wypisywanie PokeMonstera
ostream &operator<<(ostream &os, const PokeMonster &monster) {
    os << monster.name << " - " << element_name[monster.element] << "\nPOW: " << monster.power << "\nAGI: "
       << monster.agility << "\nHP: "
       << monster.health << "\nSPECIAL: "
       << monster.special->getName() << "\nCUR_EXP: "
       << monster.curr_exp << "\nGET_EXP: "
       << monster.exp_when_kill
       << "\nEXP_EVO: " << monster.exp_to_evolve << endl;
    return os;
}

// sprawdza czy dany PokeMonster istnieje
bool IsInMonsters(PokeMonster *array, const string &string_to_find, size_t size) {
    for (int i = 0; i < size; i++) {
        if (array[i].getName() == string_to_find) return true;
    }
    return false;
}

// zwraca PokeMonstera po nazwie
PokeMonster *MonsterByName(PokeMonster *array, const string &string_to_find, size_t size) {
    for (int i = 0; i < size; i++) {
        if (array[i].getName() == string_to_find) return &array[i];
    }
    return {};
}

// sprawdza czy wskazany PokeMonster jest martwy z puli PokeMonsterow
bool IsPokeMonsterDead(PokeMonster *array, const string &string_to_find, size_t size) {
    if (IsInMonsters(array, string_to_find, 6)) { return MonsterByName(array, string_to_find, 6)->isDead(); }
    return false;
}

// zwraca Superumiejetnosc po nazwie
Special *SpecialByName(const Special *array, const string &string_to_find) {
    for (int i = 0; i < 12; i++) {
        if (array[i].getName() == string_to_find) {
            return new Special(array[i].getName(), array[i].getElement(), array[i].getUsageNumber(),
                               array[i].getPoints(), array[i].getTours());
        }

    }
    return {};
}

// sprawdza czy wszystkie pokemony w danej puli sa martwe
bool AreMonstersDead(PokeMonster *array, int size) {
    for (int i = 0; i < size; i++) {
        if (!array[i].isDead()) return false;
    }
    return true;
}

// uwzglednia tablice elementow, skutecznosc atakow
int CheckElement(PokeMonster &self, PokeMonster &enemy) {
    if (self.getElement() == water && enemy.getElement() == water) { return -1; }
    else if (self.getElement() == water && enemy.getElement() == earth) { return 1; }
    else if (self.getElement() == water && enemy.getElement() == fire) { return 1; }
    else if (self.getElement() == earth && enemy.getElement() == air) { return -1; }
    else if (self.getElement() == earth && enemy.getElement() == fire) { return 1; }
    else if (self.getElement() == earth && enemy.getElement() == ice) { return 1; }
    else if (self.getElement() == earth && enemy.getElement() == steel) { return 1; }
    else if (self.getElement() == air && enemy.getElement() == earth) { return -1; }
    else if (self.getElement() == air && enemy.getElement() == ice) { return 1; }
    else if (self.getElement() == air && enemy.getElement() == steel) { return -1; }
    else if (self.getElement() == fire && enemy.getElement() == water) { return -1; }
    else if (self.getElement() == fire && enemy.getElement() == earth) { return -1; }
    else if (self.getElement() == fire && enemy.getElement() == ice) { return 1; }
    else if (self.getElement() == fire && enemy.getElement() == steel) { return 1; }
    else if (self.getElement() == ice && enemy.getElement() == water) { return -1; }
    else if (self.getElement() == ice && enemy.getElement() == earth) { return 1; }
    else if (self.getElement() == ice && enemy.getElement() == fire) { return -1; }
    else if (self.getElement() == ice && enemy.getElement() == ice) { return -1; }
    else if (self.getElement() == steel && enemy.getElement() == water) { return 1; }
    else if (self.getElement() == steel && enemy.getElement() == air) { return 1; }
    else if (self.getElement() == steel && enemy.getElement() == fire) { return -1; }
    else if (self.getElement() == steel && enemy.getElement() == steel) { return -1; }
    return 0;
}

// podstawowy atak
void Attack(PokeMonster &self, PokeMonster &enemy) {
    random_device rd;
    default_random_engine gen(rd()); //generator z biblioteki <random>
    uniform_int_distribution<> dist(0, 100);
    if (enemy.isVulnerable()) {
        if (dist(gen) <= enemy.getAgility() * 5) { cout << enemy.getName() << " uniknal ataku." << endl; }
        else {
            enemy.setHealth(enemy.getHealth() -
                            (enemy.isArmored() ? floor(((self.getPower() + CheckElement(self, enemy)) / 2)) :
                             self.getPower() + CheckElement(self, enemy)));
            cout << enemy.getName() << " stracil "
                 << (enemy.isArmored() ? floor(((self.getPower() + CheckElement(self, enemy)) / 2)) : self.getPower() +
                                                                                                      CheckElement(self,
                                                                                                                   enemy))
                 << " zycia." << endl;
            if (enemy.getHealth() > 0) cout << enemy.getName() << " zostalo " << enemy.getHealth() << " zycia." << endl;
        }
    } else {
        cout << enemy.getName() << " jest niemozliwy do trafienia." << endl;
    }
    if (enemy.getHealth() <= 0) {
        cout << enemy.getName() << " zemdlal. " << endl;
        enemy.setIsDead(true);
        cout << self.getName() << " otrzymal " << self.getExpWhenKill() << " exp." << endl;
        self.setCurrExp(self.getCurrExp() + self.getExpWhenKill());
    }
}

// pauza na zapoznanie sie z trecia na ekranie
void EnterToContinue() {
    cout << endl;
    cout << "Enter aby kontynuowac..." << endl;
    cin.sync();
    cin.get();
    cout << endl;
}

// atak z efektu co ture
void AttackEveryTour(PokeMonster &caster, PokeMonster &target, int points, string name) {
    random_device rd;
    default_random_engine gen(rd()); //generator z biblioteki <random>
    uniform_int_distribution<> dist(0, 100);

    target.setHealth(target.getHealth() - points + CheckElement(caster, target));
    cout << "Efekt: " << name << " rzucony przez " << caster.getName() << " na " << target.getName() << endl;
    cout << target.getName() << " stracil " << points + CheckElement(caster, target) << " zycia." << endl;
    if (target.getHealth() > 0) cout << target.getName() << " zostalo " << target.getHealth() << " zycia." << endl;
    if (target.getHealth() <= 0) {
        cout << target.getName() << " zemdlal. " << endl;
        target.setIsDead(true);
        cout << caster.getName() << " otrzymal " << caster.getExpWhenKill() << " exp." << endl;
        caster.setCurrExp(caster.getCurrExp() + caster.getExpWhenKill());
    }
    EnterToContinue();
}

// uzycie Superumiejetnosci
void SuperPower(PokeMonster &self, PokeMonster &enemy, vector<Effect> &effects, int &curr_tour, bool &player_action) {
    if (self.getSpecial()->getUsageNumber() > 0) {
        cout << self.getName() << " uzywa umiejetnosci " << self.getSpecial()->getName() << endl;
        self.getSpecial()->setUsageNumber(self.getSpecial()->getUsageNumber() - 1);
        Effect effect;
        effect.setName(self.getSpecial()->getName());
        effect.setPoints(self.getSpecial()->getPoints());
        effect.setTour(curr_tour + self.getSpecial()->getTours());
        effect.setMonsterCaster(&self);
        effect.setMonsterTargert(&enemy);

        if (self.getSpecial()->getName() == "Deszczyk") {
            self.setHealth(self.getHealth() + self.getHealth() * self.getSpecial()->getPoints());
        } else if (self.getSpecial()->getName() == "Skorupa_ziemska") {
            self.setIsArmored(true);
        } else if (self.getSpecial()->getName() == "Sciana_wiatru") {
            self.setIsVulnerable(false);
        } else if (self.getSpecial()->getName() == "Magmowa_skorupa") {
            self.setIsArmored(true);
        } else if (self.getSpecial()->getName() == "Sopel") {
            effect.getMonsterTargert()->setIsStunned(true);
            enemy.setIsStunned(true);
        } else if (self.getSpecial()->getName() == "Zelazna_piesc") {
            enemy.setHealth(enemy.getHealth() - self.getSpecial()->getPoints());
        } else if (self.getSpecial()->getName() == "Stalowy_unik") {
            self.setIsVulnerable(false);
        }
        effects.push_back(effect);

        player_action = false;
    } else {
        cout << "Nie mozesz wiecej uzyc tej umiejetnosci." << endl;
        EnterToContinue();
    }
}

// ewolucja i wybranie atrybtutow
void Evolve(PokeMonster &self, bool &player_action) {
    char select = ' ';
    char selected_first;
    int selected_skills = 0;
    if (self.getCurrExp() >= self.getExpToEvolve()) {
        cout << "Wybierz dwa rozne atrybuty ktore chcesz ulepszyc." << endl;
        self.setCurrExp(self.getCurrExp() - self.getExpToEvolve());
        while (selected_skills < 2) {
            while (select > '4' || select < '1' || select == selected_first) {
                cout << "[1] Sila - POW  +1 punkt" << endl;
                cout << "[2] Zrecznosc - AGI  +1 punkt" << endl;
                cout << "[3] Zycie - HP  +10 puntkow" << endl;
                cout << "[4] Zdobywany EXP - GET_EXP  +1 punkt" << endl;
                cout << "-> ";
                cin >> select;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.clear();
                if (select > '4' || select < '1') {
                    cout << "Nie ma takiej opcji wyboru, prosze wybrac poprawna opcje." << endl;
                }
                if (select == selected_first) {
                    cout << "Nie mozesz wybrac dwa razy tego samego atrybutu." << endl;
                }
            }
            selected_first = select;
            switch (select) {
                case '1':
                    self.setPower(self.getPower() + 1);
                    break;
                case '2':
                    self.setAgility(self.getAgility() + 1);
                    break;
                case '3':
                    self.setHealth(self.getHealth() + 10);
                    break;
                case '4':
                    self.setExpWhenKill(self.getExpWhenKill() + 1);
                    break;

            }
            selected_skills++;
        }
        //dokonczyc
        player_action = false;
    } else {
        cout << "Niewystarczajaca ilosc EXP aby ewoulowac " << self.getName() << endl;
        EnterToContinue();
    }
}

// status walki
void Info(PokeMonster &self, PokeMonster &enemy) {
    cout << "Twoj PokeMonster: " << endl;
    cout << self.getName() << " ma " << self.getHealth() << " punktow zycia." << endl;
    cout << "PokeMonster przeciwnika: " << endl;
    cout << enemy.getName() << " ma " << enemy.getHealth() << " punktow zycia." << endl;
}

// wbor aktywnego PokeMonstera
PokeMonster *SelectCurrMonster(PokeMonster *array) {
    string select;
    for (int i = 0; i < 6; i++) {
        if (!array[i].isDead())
            cout << array[i].getName() << " - " << element_name[array[i].getElement()] << " | HP: "
                 << array[i].getHealth() << " | POW: " << array[i].getPower() << " | AGI: " << array[i].getAgility()
                 << " | SPECIAL: " << array[i].getSpecial()->getName() << endl;
    }
    cin >> select;
    while (!IsInMonsters(array, select, 6) || IsPokeMonsterDead(array, select, 6)) {
        cout << "Wybierz poprawnego PokeMonstera" << endl;
        cin >> select;
    }
    cout << "Wybrano " << MonsterByName(array, select, 6)->getName() << endl;
    return MonsterByName(array, select, 6);
}

Difficulty difficulty_of_game = easy;
bool new_game;
string diff_lvl_selected;
string player_name;
PokeMonster player_monsters[6];
PokeMonster monsters[15];
Special special[12] = {{"Deszczyk",        water, 1, 0.3, 0},
                       {"Burza",           water, 2, 3,   2},
                       {"Skorupa_ziemska", earth, 1, 0.5, 2},
                       {"Jad_zmiji",       earth, 1, 4,   3},
                       {"Sciana_wiatru",   air,   2, 0,   0},
                       {"Tornado",         air,   2, 2,   3},
                       {"Kula_ognia",      fire,  1, 5,   2},
                       {"Magmowa_skorupa", fire,  1, 0.5, 2},
                       {"Sopel",           ice,   2, 0,   1},
                       {"Zamiec",          ice,   1, 2,   5},
                       {"Zelazna_piesc",   steel, 3, 7,   0},
                       {"Stalowy_unik",    steel, 3, 5,   0}};

Enemy enemy_list[4];

// odczyt stanu gry z pliku
void LoadGame(char select, const string &monster_select, bool &in_menu) {
    ifstream file_stream;
    string file_name;
    int file_num = 0;
    string name, element, special_power;
    int pow, agi, hp, currxp, xptoe, dropxp;
    bool is_dead;
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserName(username, &username_len);
    string path_to_file;
    path_to_file = path_to_file + "C:\\Users\\" + username + "\\Saved Games\\PokeMonsters\\";

    try {
        for (const filesystem::directory_entry &entry: filesystem::directory_iterator(path_to_file)) {
            if (entry.path().string().substr(entry.path().string().length() - 6, 6) == ".pmsav") {
                std::cout << entry.path().filename() << std::endl;
                file_num++;
            }
        }
    }
    catch (filesystem::filesystem_error const &ex) {
        filesystem::create_directories(path_to_file);
        for (const filesystem::directory_entry &entry: filesystem::directory_iterator(path_to_file)) {
            if (entry.path().string().substr(entry.path().string().length() - 6, 6) == ".pmsav") {
                std::cout << entry.path().filename() << std::endl;
                file_num++;
            }
        }
    }

    if (file_num > 0) {
        cout << "Podaj nazwe pliku do wczytania (bez rozszerzenia, np. save01)" << endl;
        cout << "Wpisz -back by powrocic do menu" << endl;
        while (!file_stream.is_open()) {
            cin >> file_name;
            file_stream.open(path_to_file + file_name + ".pmsav");
            if (file_name == "-back") break;
            if (!file_stream.is_open()) {
                cout << "Plik o takiej nazwie nie istnieje, prosze podac poprawna nazwe pliku." << endl;
            }
        }
        if (file_name == "-back") {
            in_menu = true;
            return;
        } else if (file_stream.is_open()) {
            file_stream >> name;
            if (name == "0") difficulty_of_game = easy;
            else if (name == "1") difficulty_of_game = medium;
            else difficulty_of_game = hard;
            file_stream >> name;
            player_name = name;
            for (int i = 0; i < 6; i++) {
                file_stream >> name >> element >> pow >> agi >> hp >> currxp >> xptoe >> dropxp >> special_power
                            >> is_dead;
                player_monsters[i].setName(name);
                if (element == "0") player_monsters[i].setElement(water);
                else if (element == "1") player_monsters[i].setElement(earth);
                else if (element == "2") player_monsters[i].setElement(air);
                else if (element == "3") player_monsters[i].setElement(fire);
                else if (element == "4") player_monsters[i].setElement(ice);
                else player_monsters[i].setElement(steel);
                player_monsters[i].setPower(pow);
                player_monsters[i].setAgility(agi);
                player_monsters[i].setHealth(hp);
                player_monsters[i].setCurrExp(currxp);
                player_monsters[i].setExpToEvolve(xptoe);
                player_monsters[i].setExpWhenKill(dropxp);
                player_monsters[i].setSpecial(SpecialByName(special, special_power));
                player_monsters[i].setIsDead(is_dead);
            }
            for (Enemy &enemy: enemy_list) {
                file_stream >> name >> is_dead;
                enemy.setName(name);
                enemy.setIsDead(is_dead);
                for (int j = 0; j < 4 + difficulty_of_game; j++) {
                    file_stream >> name >> element >> pow >> agi >> hp >> currxp >> xptoe >> dropxp
                                >> special_power
                                >> is_dead;
                    enemy.getMonsters()[j].setName(name);
                    if (element == "0") enemy.getMonsters()[j].setElement(water);
                    else if (element == "1") enemy.getMonsters()[j].setElement(earth);
                    else if (element == "2") enemy.getMonsters()[j].setElement(air);
                    else if (element == "3") enemy.getMonsters()[j].setElement(fire);
                    else if (element == "4") enemy.getMonsters()[j].setElement(ice);
                    else enemy.getMonsters()[j].setElement(steel);
                    enemy.getMonsters()[j].setPower(pow);
                    enemy.getMonsters()[j].setAgility(agi);
                    enemy.getMonsters()[j].setHealth(hp);
                    enemy.getMonsters()[j].setCurrExp(currxp);
                    enemy.getMonsters()[j].setExpToEvolve(xptoe);
                    enemy.getMonsters()[j].setExpWhenKill(dropxp);
                    enemy.getMonsters()[j].setSpecial(SpecialByName(special, special_power));
                    enemy.getMonsters()[j].setIsDead(is_dead);
                }
            }
            file_stream.close();
            file_stream.clear();
            in_menu = false;
            cout << "Poprawnie wczytano stan gry" << endl;
            cout << "Nazwa gracza: " << player_name << endl;
        }
    } else { cout << "Brak plikow do wczytania." << endl; }
}

// zapis stanu gry do pliku
void SaveGame() {
    ofstream file_stream;
    string file_name;
    char select;
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserName(username, &username_len);
    string path_to_file;
    bool overwrite = true;
    path_to_file = path_to_file + "C:\\Users\\" + username + "\\Saved Games\\PokeMonsters\\";

    try {
        filesystem::directory_entry(path_to_file).exists();
    }
    catch (filesystem::filesystem_error const &ex) {
        filesystem::create_directories(path_to_file);
    }
    cout << "Podaj nazwe pliku do ktorego chcesz zapisac (bez rozszerzenia)" << endl;
    cout << "Wpisz -back by powrocic do menu" << endl;
    while (!file_stream.is_open()) {
        overwrite = true;
        getline(cin, file_name);
        if (file_name == "-back") return;

        // zabezpieczenie przed przypadkowym nadpisaniem pliku
        if (filesystem::directory_entry(path_to_file + file_name + ".pmsav").exists()) {
            cout << "Plik o podanej nazwie istnieje." << endl;
            cout << "Czy chcesz go nadpisac?" << endl;
            select = ' ';
            while (select > '2' || select < '1') {
                cout << "[1] Tak" << endl;
                cout << "[2] Nie" << endl;;
                cout << "-> ";
                cin >> select;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.clear();
                if (select > '2' || select < '1') {
                    cout << "Nie ma takiej opcji wyboru, prosze wybrac poprawna opcje." << endl;
                }
            }

            switch (select) {
                case '1':
                    overwrite = true;
                    break;
                case '2':
                    cout << "Podaj nazwe pliku do ktorego chcesz zapisac (bez rozszerzenia)" << endl;
                    cout << "Wpisz -back by powrocic do menu" << endl;
                    overwrite = false;
                    break;
            }
        }
        if (overwrite) {
            file_stream.open(path_to_file + file_name + ".pmsav");
        }
    }
    if (file_stream.is_open()) {
        file_stream << difficulty_of_game << endl;
        file_stream << player_name << endl;
        for (PokeMonster &player_monster: player_monsters) {
            file_stream << player_monster.getName() << " " << player_monster.getElement() << " "
                        << player_monster.getPower() << " " << player_monster.getAgility() << " "
                        << player_monster.getHealth() << " " << player_monster.getCurrExp() << " "
                        << player_monster.getExpToEvolve() << " " << player_monster.getExpWhenKill() << " "
                        << player_monster.getSpecial()->getName() << " " << player_monster.isDead()
                        << endl;
        }
        for (Enemy &enemy: enemy_list) {
            file_stream << enemy.getName() << " " << enemy.isDead() << endl;
            for (int k = 0; k < 4 + difficulty_of_game; k++) {
                file_stream << enemy.getMonsters()[k].getName() << " "
                            << enemy.getMonsters()[k].getElement() << " "
                            << enemy.getMonsters()[k].getPower() << " "
                            << enemy.getMonsters()[k].getAgility() << " "
                            << enemy.getMonsters()[k].getHealth() << " "
                            << enemy.getMonsters()[k].getCurrExp() << " "
                            << enemy.getMonsters()[k].getExpToEvolve() << " "
                            << enemy.getMonsters()[k].getExpWhenKill() << " "
                            << enemy.getMonsters()[k].getSpecial()->getName() << " "
                            << enemy.getMonsters()[k].isDead() << endl;

            }
        }
        file_stream.close();
        file_stream.clear();
    } else cout << ("Blad zapisu") << endl;
    cout << "Poprawnie zapisano stan gry" << endl;
    cout << "Nazwa pliku: " << file_name + ".pmsav" << endl;
    cout << endl;
}

// wyswietla informacje o superumiejetnosciach
void InfoAboutSpecials() {
    cout << endl;
    cout
            << "+---------------------+--------------------------------------------------------------------+-------------+\n"
               "| Nazwa umiejetnosci  | Opis                                                               | Ilosc uzyc  |\n"
               "+---------------------+--------------------------------------------------------------------+-------------+\n"
               "| Deszczyk            | umiejetnosc leczy o 30% aktualnego zycia PokeMonstera              |      1      |\n"
               "| Burza               | umiejetnosc zadaje po 3 DMG przez 2 tury                           |      2      |\n"
               "| Skorupa ziemska     | umiejetnosc zmniejsza otrzymywane obrazenia o polowe przez 2 tury  |      1      |\n"
               "| Jad zmiji           | umiejetnosc zatruwa przeciwnika zadajac po 4 DMG przez 2 tury      |      1      |\n"
               "| Sciana wiatru       | umiejetnosc blokuje wszystkie obrazenia na czas trwania tury       |      2      |\n"
               "| Tornado             | umiejetnosc zadaje po 2 DMG przez 3 tury                           |      2      |\n"
               "| Kula ognia          | umiejetnosc zadaje po 5 DMG przez 2 tury                           |      1      |\n"
               "| Magmowa skorupa     | umiejetnosc zmniejsza otrzymywane obrazenia o polowe przez 2 tury  |      1      |\n"
               "| Sopel               | umiejetnosc zamraza przeciwnika na 2 tury                          |      2      |\n"
               "| Zamiec              | umiejetnosc zadaje po 2 DMG przez 5 tur                            |      1      |\n"
               "| Zelazna piesc       | umiejetnosc zadaje 7 DMG w momencie uzycia                         |      3      |\n"
               "| Stalowy unik        | umiejetnosc pozwala uniknac obrazen                                |      3      |\n"
               "+---------------------+--------------------------------------------------------------------+-------------+"
            << endl;
    cout << endl;

}

// wyswietla informacje o PokeMonsterach
void InfoAboutMonsters() {
    for (int i = 0; i < 15; i++) {
        cout << "--------" << i + 1 << "--------" << endl;
        cout << monsters[i] << endl;
    }
    cout << endl;
}

// wyswietla informacje o zaleznosci obrazen od elementu PokeMonstera
void InfoAboutElements() {
    cout << endl;
    cout << "+--------------------------+-------+---------+-----------+--------+------+-------+\n"
            "| Stworzenie Atakujace \\/  | WODA  | ZIEMIA  | POWIETRZE | OGIEN  | LOD  | STAL  |\n"
            "+--------------------------+-------+---------+-----------+--------+------+-------+\n"
            "| WODA                     |  -1   |   +1    |     0     |   +1   |   0  |   0   |\n"
            "| ZIEMIA                   |   0   |    0    |    -1     |   +1   |  +1  |  +1   |\n"
            "| POWIETRZE                |   0   |   -1    |     0     |    0   |  +1  |  -1   |\n"
            "| OGIEN                    |  -1   |   -1    |     0     |    0   |  +1  |  +1   |\n"
            "| LOD                      |  -1   |   +1    |     0     |   -1   |  -1  |   0   |\n"
            "| STAL                     |  +1   |    0    |    +1     |   -1   |   0  |  -1   |\n"
            "+--------------------------+-------+---------+-----------+--------+------+-------+" << endl;
    cout << endl;
}

// pokazuje glowne menu gry
void ShowMenu(char &select, string &monster_select) {
    new_game = false;
    bool in_menu = true;
    for (PokeMonster &player_monster: player_monsters) {
        player_monster = {};
    }
    const char *st;
    st = "                                                                                                                        \n"
         "                           `.--/+oooo//-.`                               `..:/+oooo//-.`                                \n"
         "                        ./shdhyo+/:/++shmdho-.                       `./ydmdyo++:/++shhdho-`                            \n"
         "                      -yNMd/.        `:ymMMMMmy/                   .odNMMMMho.        `-sNMdo`                          \n"
         "                     sMMMh`          -:--/hNNho/-                 `/+smMmo:--:.          :MMMm-                         \n"
         "                    :MMMM-   /   ```  `-   :/ody`.+o+/--```.-:/o+:`-Ny/+`   :   ``   `/   hMMMd                         \n"
         "                    oMMMM   /m`+ssshhshm`  .mMMs :odNMMMMMMMMMMNh+`.MMMo   +Moyhysss:+m   oMMMM                         \n"
         "                    /MMhd-  oMMh`   :yMMNsomMMM`.ooosdNMMMMMMmyooo+ sMMMyohMMmo.   /NMM   hoMMd                         \n"
         "                     dMy .  -MM`      :mMMMMd+/``ymMMMMMMMMMMMMMMh/ -/yMMMMMs       sMh  ``.MM-                         \n"
         "                     `dM-    +My.      `mMMN+syhhs++yMMMMMMMMMmo/oyhhsoyMMM+       +Nd`    hM+                          \n"
         "                      `yN/    -hMh:     .NMMMMMMMMMMdsmMMMMMMhyNMMMMMMMMMMs     `omNo`   `hN:                           \n"
         "                        /Nh:    :mMh`    sMMd:``.:smMMmMMMMMNNMMh+-``.+MMM`    :NMs`   .oNh.                            \n"
         "                         .sNms/.`.mMs    oMM+      `oMMMMMMMMMd-       mMM    .NM+ .-+hNd:                              \n"
         "                           .yMMh: /MM    /MMm-    `` /NMMMMMMh` .    `sMMm    oMd .+NMN/`                               \n"
         "                            `hMm` +MN    `NMMNs-`  h-`oMMMMMN.`s/  ./dMMMs    +Mm` +MM:                                 \n"
         "                             -MMssNMo     +NMNmdhs+mm//MMMMMyo/MsoyhmNMMd`    `NMd+NMh                                  \n"
         "                              MMMMmo       :dNmmhosdN-NNMMMMmh+NyosdmNms`      -hNMMMo                                  \n"
         "                             :Nmh+.          -+ydmd+:-NMMMMMMy.:ymmhs:`         `:sdmh                                  \n"
         "                             ..`                `+oy+`:NMMMMs..ys+:                 .-`                                 \n"
         "                                                :MNy+  hMMMM- -omMh                                                     \n"
         "                                                :My/:. hNNNN: :.ydh                                                     \n"
         "                                                :M: ho -/-/:.-y/ hh                                                     \n"
         "                                                :M/ dM/MMoMMdoN/ mh                                                     \n"
         "                                                :Mo y+ -+-//`.s: Mh                                                     \n"
         "                                                -My mM:MM+NMdoM/-Mh                                                     \n"
         "                                                 NMm+/ -+:o/`./yMM+                                                     \n"
         "                                                 -mMMNmyo+oshNMMMs                                                      \n"
         "                                                  `smMMMMMMMMMMh:                                                       \n"
         "                                                    `+dMMMMMmy-`                                                        \n"
         "                                                      `-ohy/.                                                           \n"
         "                                                         `                                                              \n"
         "                                                                                                                        \n"
         "       +/:-.`               .-               `.:-      `                               `-                               \n"
         "      .MMMMNmho-`          sNh              .dNMh    `ydh+                            .hM                               \n"
         "       /oMMNdmMMm`   ``   -MMh   ``         :MMMM`   oMMMh    `    /o.``.`    `--.    oMM`                              \n"
         "        :MMh `/MM:`/syys- :MMs .yhs  `-::-` -MMMM+  `NMMMh .oyyys` sMmhdMm:  .dMNmh/``sMM-.  ``-::.  oy//ss:            \n"
         "        -MMs `hMM+oMd.-Mh :MMo:NNs` sNNNMMd `MMMMd  sMMMMo mMo.oM+ oMM/.hMN -NMh`+MMsdNMMNN -hNNNMM/ sMMhoMM.           \n"
         "         MMo/mMm/ hMo  MM`.MMmMd-  +My-./MM. mMhMM-`NMdMM/ MM: /Md oMM  oMM dMMo .Nh `+MM-. mM:..hMh oMM` dMs           \n"
         "         MMNdo-   hMo .MM: MMMM-   yM/./oMM- yMhoMh+MhoMM. MM: oMM :MM  hMd `oNMm/`   :MM  `MM`-+dMh /MM  --`           \n"
         "         NM/      hMh./MM: MMyMM:  hMNhyso/` +Md`mMNM.oMm  MM+.yMM .MM  hM+  - +NMh.  .MM  -MMmhyo+- -MM                \n"
         "         hM:      sMMMMMM- dM:-mM/ yMm  `NM` -MM :MMs hMs  dMMMMMN  MM  mM. -My``yMh   MN   MM+  +My  MM                \n"
         "         hM:       ``.--`  hM  `yM//MMs:oMy   NM  /d` hM/   ``---`  ys  ys   /dNsNN-   yh   mMm/-mM-  so                \n"
         "         .y.               `+    :+`.+ssyo`   /m   `  hh            `         `-ss.     `   `:osyy/                     \n"
         "                                               `      .`                                                                \n"
         "                                                                                                                        ";
    // efekt wypisywania po znaku (szybki)
    printf(st);
    cout << endl;

    while (in_menu) {
        select = ' ';
        while (select > '5' || select < '1') {
            cout << "[1] Nowa gra" << endl;
            cout << "[2] Wczytaj gre" << endl;
            cout << "[3] Informacje o umiejetnosciach specjalnych" << endl;
            cout << "[4] Tablica zywiolow" << endl;
            cout << "[5] Wyjscie" << endl;
            cout << "-> ";
            cin >> select;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.clear();
            if (select > '5' || select < '1') {
                cout << "Nie ma takiej opcji wyboru, prosze wybrac poprawna opcje." << endl;
            }
        }

        switch (select) {
            case '1':
                new_game = true;
                in_menu = false;
                cout << "Podaj swoje imie (nazwe postaci), bez spacji: " << endl;
                cin >> player_name;
                select = ' ';
                while (select > '3' || select < '1') {
                    cout << "[1] Latwy" << endl;
                    cout << "[2] Sredni" << endl;
                    cout << "[3] Trudny" << endl;
                    cout << "-> ";
                    cin >> select;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.clear();
                    if (select > '3' || select < '1') {
                        cout << "Nie ma takiej opcji wyboru, prosze wybrac poprawna opcje." << endl;
                    }
                }
                switch (select) {
                    case '1':
                        difficulty_of_game = easy;
                        diff_lvl_selected = "Latwy";
                        break;
                    case '2':
                        difficulty_of_game = medium;
                        diff_lvl_selected = "Sredni";
                        break;
                    case '3':
                        difficulty_of_game = hard;
                        diff_lvl_selected = "Trudny";
                        break;
                }
                cout << "Nazwa gracza: " << player_name << endl;
                cout << "Wybrany poziom trudnosci: " << diff_lvl_selected << endl;
                cout << endl;
                cout << "Wyswietlona zostanie lista PokeMonsterow z ich statystykami." << endl;
                cout << "Wybierz 6 PokeMonsterow wpisujac ich nazwe." << endl;
                cout << "POW to sila ataku, AGI to szansa na unik, HP to punkty zycia." << endl;
                cout << "Zywioly maja rozna efektywnosc podczas ataku innych zywiolow. (Tabela zywiolow)" << endl;
                cout << "Kazdego stworka mozesz wybrac tylko raz: " << endl;
                cout << "----------------------------------------------------" << endl;
                EnterToContinue();
                cout << endl;
                InfoAboutMonsters();
                for (int i = 0; i < 6; i++) {
                    cout << "-> ";
                    cin >> monster_select;
                    while (!IsInMonsters(monsters, monster_select, sizeof(monsters) / sizeof(monsters[0])) ||
                           IsInMonsters(player_monsters, monster_select,
                                        sizeof(player_monsters) / sizeof(player_monsters[0]))) {
                        if (!IsInMonsters(monsters, monster_select, sizeof(monsters) / sizeof(monsters[0]))) {
                            cout << "Wybierz poprawnego stworka." << endl;
                        }
                        if (IsInMonsters(player_monsters, monster_select,
                                         sizeof(player_monsters) / sizeof(player_monsters[0]))) {
                            cout << "Masz juz tego PokeMonstera." << endl;
                        }
                        cout << "-> ";
                        cin >> monster_select;
                    }
                    player_monsters[i] = *MonsterByName(monsters, monster_select,
                                                        sizeof(monsters) / sizeof(monsters[0]));
                }
                break;
            case '2':
                // wczytywanie gry
                LoadGame(select, monster_select, in_menu);
                break;
            case '3':
                InfoAboutSpecials();
                break;
            case '4':
                InfoAboutElements();
                break;
            case '5':
                abort();
        }
    }
}

// mechaniki gry
int main() {
    // konsola windowsowa w trybie fullscreen
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    Generator(monsters, special);

    char select;
    string monster_select;
    ShowMenu(select, monster_select);

    if (new_game) {
        Enemy enemy1("Bob", monsters, difficulty_of_game);
        Enemy enemy2("Dragon", monsters, difficulty_of_game);
        Enemy enemy3("Kiki", monsters, difficulty_of_game);
        Enemy enemy4("Boss", monsters, difficulty_of_game);
        enemy_list[0] = enemy1;
        enemy_list[1] = enemy2;
        enemy_list[2] = enemy3;
        enemy_list[3] = enemy4;
        new_game = false;
    }

    //rozgrywka
    int curr_e_monster = 0;
    PokeMonster *curr_player_monster;
    PokeMonster *curr_enemy_monster;
    PokeMonster temp_monster;
    vector<Effect> effects;
    bool player_move = false;
    bool *player_action = &player_move;
    int curr_tour = 0;
    for (int i = 0; i < 4; i++) {
        cout << endl;
        // reset uzyc umiejetnosci po kazdym przeciwniku
        for (PokeMonster monster: player_monsters) {
            monster.getSpecial()->setUsageNumber(
                    SpecialByName(special, monster.getSpecial()->getName())->getUsageNumber());
        }
        while (!enemy_list[i].isDead()) {
            if (!enemy_list[i].isDead()) { cout << "Przeciwnik " << enemy_list[i].getName() << " przybywa" << endl; }
            // reset parametow tury po kazdym przeciwniku
            curr_tour = 0;
            curr_e_monster = 0;
            effects.clear();
            select = ' ';
            while (select > '5' || select < '1') {
                cout << "[1] Walcz" << endl;
                cout << "[2] Zapisz gre" << endl;
                cout << "[3] Informacje o umiejetnosciach specjalnych" << endl;
                cout << "[4] Tabela zywiolow" << endl;
                cout << "[5] Wyjscie do menu" << endl;
                cout << "-> ";
                cin >> select;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.clear();
                if (select > '5' || select < '1') {
                    cout << "Nie ma takiej opcji wyboru, prosze wybrac poprawna opcje." << endl;
                }
            }
            switch (select) {
                case '1':
                    // walka z przeciwnikami
                    cout << "Wybierz swojego PokeMonstera do walki: " << endl;
                    curr_player_monster = SelectCurrMonster(player_monsters);
                    curr_enemy_monster = &enemy_list[i].getMonsters()[curr_e_monster];
                    while (!AreMonstersDead(enemy_list[i].getMonsters(), 4 + difficulty_of_game)) {
                        cout << "AKTUALNA TURA: " << curr_tour << endl;

                        // reset statusow na poczatku kazdej tury
                        curr_player_monster->setIsStunned(false);
                        curr_player_monster->setIsArmored(false);
                        curr_player_monster->setIsVulnerable(true);
                        curr_enemy_monster->setIsStunned(false);
                        curr_enemy_monster->setIsArmored(false);
                        curr_enemy_monster->setIsVulnerable(true);

                        // wykonanie efektow
                        for (Effect effect: effects) {
                            if (curr_tour <= effect.getTour() && effect.getName() != "Skorupa_ziemska" &&
                                effect.getName() != "Sciana_wiatru" && effect.getName() != "Magmowa_skorupa" &&
                                effect.getName() != "Sopel" && effect.getName() != "Stalowy_unik") {
                                AttackEveryTour(*effect.getMonsterCaster(), *effect.getMonsterTargert(),
                                                effect.getPoints(), effect.getName());
                            }
                            if (curr_tour <= effect.getTour() && effect.getName() == "Sopel") {
                                effect.getMonsterTargert()->setIsStunned(true);
                            }
                            if (curr_tour <= effect.getTour() && effect.getName() == "Skorupa_ziemska" ||
                                effect.getName() == "Magmowa_skorupa") {
                                effect.getMonsterCaster()->setIsArmored(true);
                            }

                        }

                        // zmiana PokeMonstera przeciwnika po smierci
                        if (curr_enemy_monster->isDead()) {
                            curr_enemy_monster = &enemy_list[i].getMonsters()[curr_e_monster + 1];
                            curr_e_monster++;
                        }
                        cout << endl;

                        // podanie statustu walki
                        Info(*curr_player_monster, *curr_enemy_monster);
                        cout << endl;

                        // ruch gracza
                        if (!curr_player_monster->isStunned()) {
                            *player_action = true;
                            while (*player_action) {
                                cout << "Twoj ruch: " << endl;
                                select = ' ';
                                while (select > '9' || select < '0') {
                                    cout << "[1] Atakuj" << endl;
                                    cout << "[2] Uzyj Superumiejetnosci" << " - liczba uzyc: "
                                         << curr_player_monster->getSpecial()->getUsageNumber() << endl;
                                    cout << "[3] Ewouluj" << endl;
                                    cout << "[4] Zmien PokeMonstera" << endl;
                                    cout << "[5] Info o Twoim PokeMonsterze" << endl;
                                    cout << "[6] Info o PokeMonsterze przeciwnika" << endl;
                                    cout << "[7] Info o nalozonych efektach" << endl;
                                    cout << "[8] Informacje o umiejetnosciach specjalnych" << endl;
                                    cout << "[9] Tabela zywiolow" << endl;
                                    cout << "[0] Wyjscie do menu" << endl;
                                    cout << "-> ";
                                    cin >> select;
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cin.clear();
                                    if (select > '9' || select < '0') {
                                        cout << "Nie ma takiej opcji wyboru, prosze wybrac poprawna opcje." << endl;
                                    }
                                }
                                switch (select) {
                                    case '1':
                                        Attack(*curr_player_monster, *curr_enemy_monster);
                                        *player_action = false;
                                        break;
                                    case '2':
                                        SuperPower(*curr_player_monster, *curr_enemy_monster, effects, curr_tour,
                                                   *player_action);
                                        break;
                                    case '3':
                                        Evolve(*curr_player_monster, *player_action);
                                        break;
                                    case '4':
                                        cout << "Wybierz PokeMonstera - aktualny: " << curr_player_monster->getName()
                                             << endl;
                                        cout
                                                << "Jezeli wybierzesz aktualnie wybranego PokeMonstera, nie stracisz tury, tylko powrocisz do menu walki: "
                                                << endl;
                                        temp_monster = *curr_player_monster;
                                        curr_player_monster = SelectCurrMonster(player_monsters);
                                        if (temp_monster.getName() != curr_player_monster->getName()) {
                                            *player_action = false;
                                        }
                                        cout << endl;
                                        break;
                                    case '5':
                                        cout << *curr_player_monster << endl;
                                        break;
                                    case '6':
                                        cout << "Nazwa: " << curr_enemy_monster->getName() << endl;
                                        cout << "Zywiol: " << element_name[curr_enemy_monster->getElement()] << endl;
                                        cout << "HP: " << curr_enemy_monster->getHealth() << endl;
                                        cout << endl;
                                        break;
                                    case '7':
                                        for (Effect effect: effects) {
                                            if (curr_tour <= effect.getTour()) {
                                                cout << "Efekt " << effect.getName() << " nalozony na "
                                                     << effect.getMonsterTargert()->getName() << " do tury "
                                                     << effect.getTour() + 1 << endl;
                                            }
                                        }
                                        cout << endl;
                                        break;
                                    case '8':
                                        InfoAboutSpecials();
                                        break;
                                    case '9':
                                        InfoAboutElements();
                                        break;
                                    case '0':
                                        cout
                                                << "Jezeli wyjdziesz wszystkie twoje PokeMonstery zemdleja, a ty przegrasz gre."
                                                << endl;
                                        cout
                                                << "Bedziesz musial rozpoczac gre od nowa lub wczytac wczesniej wykonany zapis gry."
                                                << endl;
                                        cout << "Czy na pewno chcesz wyjsc?" << endl;
                                        select = ' ';
                                        while (select > '2' || select < '1') {
                                            cout << "[1] Tak" << endl;
                                            cout << "[2] Nie" << endl;
                                            cout << "-> ";
                                            cin >> select;
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            cin.clear();
                                            if (select > '2' || select < '1') {
                                                cout << "Nie ma takiej opcji wyboru, prosze wybrac poprawna opcje."
                                                     << endl;
                                            }
                                        }
                                        switch (select) {
                                            case '1':
                                                for (PokeMonster &player_monster: player_monsters) {
                                                    curr_player_monster = &player_monster;
                                                    curr_player_monster->setIsDead(true);
                                                    curr_player_monster->isDead();
                                                }
                                                *player_action = false;
                                                select = ' ';
                                                break;
                                            case '2':
                                                select = ' ';
                                                break;
                                        }

                                        break;
                                }
                            }
                        } else {
                            cout << "Twoj PokeMonster: " << curr_enemy_monster->getName() << " jest ogluszony."
                                 << endl;
                        }
                        EnterToContinue();

                        // sprawdza czy gracz nie przegral
                        if (AreMonstersDead(player_monsters, 6)) {
                            cout << "Wszystkie twoje PokeMonstery zemdlaly." << endl;
                            cout << "Nie posiadasz wiecej PokeMonsterow." << endl;
                            cout << "Niestety, ale przegrales :(" << endl;
                            select = ' ';
                            EnterToContinue();
                            break;
                        }

                        // ruch przeciwnika
                        if (!curr_enemy_monster->isStunned()) {
                            if (!curr_enemy_monster->isDead()) {
                                if (curr_enemy_monster->getCurrExp() >= curr_enemy_monster->getExpToEvolve()) {

                                    // ewolucja przeciwnika
                                    curr_enemy_monster->setCurrExp(
                                            curr_enemy_monster->getCurrExp() - curr_enemy_monster->getExpToEvolve());
                                    int old_evo = 0;
                                    int curr_evo;
                                    random_device rd;
                                    default_random_engine gen(rd()); //generator z biblioteki <random>
                                    uniform_int_distribution<> dist(1, 4);
                                    curr_evo = dist(gen);
                                    for (int k = 0; k < 2; k++) {
                                        while (old_evo == curr_evo) {
                                            curr_evo = dist(gen);
                                        }
                                        if (curr_evo == 1) {
                                            curr_enemy_monster->setPower(curr_enemy_monster->getPower() + 1);
                                        } else if (curr_evo == 2) {
                                            curr_enemy_monster->setAgility(curr_enemy_monster->getAgility() + 1);
                                        } else if (curr_evo == 3) {
                                            curr_enemy_monster->setExpWhenKill(
                                                    curr_enemy_monster->getExpWhenKill() + 1);
                                        } else { curr_enemy_monster->setHealth(curr_enemy_monster->getHealth() + 10); }
                                        old_evo = curr_evo;
                                    }
                                    cout << "Przeciwnik ewoulowal " << curr_enemy_monster->getName() << endl;
                                    EnterToContinue();
                                } else {

                                    // uzycie supermocy przeciwnika (20% - 33% szans, zalezy od poziomu trudnosci), jezeli jest ona dostepna
                                    random_device rd;
                                    default_random_engine gen(rd()); //generator z biblioteki <random>
                                    uniform_int_distribution<> dist(1, 5 - difficulty_of_game);
                                    if (curr_enemy_monster->getSpecial()->getUsageNumber() > 0 && dist(gen) == 1) {
                                        SuperPower(*curr_enemy_monster, *curr_player_monster, effects, curr_tour,
                                                   *player_action);
                                        EnterToContinue();
                                    } else {

                                        // atak przeciwnika
                                        cout << "Przeciwnik atakuje." << endl;
                                        Attack(*curr_enemy_monster, *curr_player_monster);
                                        EnterToContinue();

                                        // sprawdza czy gracz nie przegral
                                        if (AreMonstersDead(player_monsters, 6)) {
                                            cout << "Wszystkie twoje PokeMonstery zemdlaly." << endl;
                                            cout << "Nie posiadasz wiecej PokeMonsterow." << endl;
                                            cout << "Niestety, ale przegrales :(" << endl;
                                            select = ' ';
                                            EnterToContinue();
                                            break;
                                        }
                                    }
                                }
                            }
                        } else {
                            cout << "PokeMonster przeciwnika: " << curr_enemy_monster->getName() << " jest ogluszony."
                                 << endl;
                            EnterToContinue();
                        }

                        // sprawdza czy gracz ma zywego PokeMonstera
                        if (curr_player_monster->isDead()) {
                            cout << "Musisz wybrac nowego PokeMnostera" << endl;
                            cout << endl;
                            curr_player_monster = SelectCurrMonster(player_monsters);

                        }

                        // zwiekszenie licznika tur pod koniec tury
                        curr_tour++;
                    }
                    if (AreMonstersDead(player_monsters, 6)) {
                        break;
                    } else {
                        enemy_list[i].setIsDead(true);
                        cout << endl;
                        cout << "WYGRALES WALKE Z: " << enemy_list[i].getName() << endl;
                    }
                    break;
                case '2':
                    // zapis gry
                    SaveGame();
                    break;
                case '3':
                    InfoAboutSpecials();
                    break;
                case '4':
                    InfoAboutElements();
                    break;
                case '5':
                    // powrot do menu
                    i = 0;
                    ShowMenu(select, monster_select);
                    break;
            }
            // powrot do menu jezeli gracz przegral gre
            if (AreMonstersDead(player_monsters, 6)) {
                i = 0;
                ShowMenu(select, monster_select);
            }
        }
    }
    cout << "BRAWO!" << endl;
    cout << "WYGRALES GRE " << player_name << endl;
    cout << "TO BYL " << difficulty_of_game << " POZIOM TRUDNOSCI" << endl;
    cout << endl;
    EnterToContinue();
    select = ' ';
    monster_select = "";
    ShowMenu(select, monster_select);
}
