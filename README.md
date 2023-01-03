# CPP_Projekt_PokeMonster
Projekt zaliczeniowy z CPP w PJATK
Projekt, którego tematem jest aplikacja konsolowa symulująca grę walki turowej z 
implementacją oddziaływań między przeciwnikami. Aplikacja uruchamiana jest z poziomu linii poleceń. Bazując na 
komendach czytanych z klawiatury, wykonuje odpowiednie zagrania dla postaci. Gracz posiada zestaw 6 stworzeń którymi kieruje. Celem gry jest pokonanie wszystkich 
przeciwników stojących na drodze, z jak najmniejszym kosztem dla swojej drużyny.

Opis rozgrywki:
Rozgrywka dzieli się na co najmniej 4 rundy, przy czym każda runda posiada 
przynajmniej 4 przeciwników. Wszyscy przeciwnicy są losowani z puli 15 stworzeń, z których 
gracz może wybrać swój zespół.
Na początku rozgrywki gracz może wybrać sobie zespół składający się z sześciu stworzeń z
predefiniowanej puli.
Rozgrywka dzielona jest na tury gracz–przeciwnik, gdzie w jednej turze można wykonać 
następujące akcje:
• Użycie umiejętności specjalnej/ataku, lub
• Wymiana stworzenia, lub
• Ewolucja stworzenia.
Po zmniejszeniu statystyki Punkty Życia stworzenia, mdleje ono, i nie można go ponownie 
wykorzystać do końca walki. Po pokonaniu przeciwnika przez gracza, pojawia się 
komunikat dający możliwość zapisania i wyjścia z gry albo kontynuowania rozgrywki. 
W momencie pokonania wszystkich przeciwników gra się kończy zwycięstwem gracza.

Wymagania funkcjonalne:
Każde stworzenie musi posiadać atrybuty definiujące jej zachowania i wpływ na rozgrywkę, w 
atrybuty wlicza się:
• Siła – definiuje, ile obrażeń może zadać stworzenie jednym atakiem;
• Zręczność – definiuje, jaka jest szansa na uniknięcie ataku przeciwnika;
• Punkty Życia – definiuje, ile obrażeń może przyjąć stworzenie zanim zemdleje;
• Moc Specjalna – określa charakterystyki mocy specjalnej dla danego stworzenia oraz 
maksymalną liczbę jej użyć w jednej walce.
• Punkty EXP – ile punktów EXP jest przyznawane za pokonanie przeciwnika. Przy czym Moc Specjalna musi być adekwatna do typu stworzenia (np. stworzenie typu 
wodnego, nie może użyć tornada czy ognistego ataku jako mocy specjalnej). Moc specjalna 
również dzieli się na moce ofensywne i defensywne, które mogą wpłynąć tymczasowo (ilość 
tur) na statystyki gracza lub przeciwnika. 
Każde stworzenie posiada również swój typ (Woda, Ziemia, Powietrze, Ogień, Lód, Stal), który
warunkuje to jak dobrze ich ataki wpływają na inne stworzenia (zgodnie z tabelą interakcji). Program posiada pulę przynajmniej 15 stworzeń, z których gracz może wybrać 
swoją drużynę, oraz z których losowane są drużyny przeciwników. 
Gra posiada przynajmniej 4 przeciwników, każdy z nich posiada przynajmniej 4 stworzenia. Zaimplementowane zostały poziomy trudności które te wartości 
zmieniają.
Wybór stworzeń oraz ataków ma się odbywać przez klawiaturę. Interfejs użytkownika posiada instrukcję obsługi.
Każde stworzenie może po uzyskaniu określonej dla niego liczby EXP ewoluować, zwiększając 
swoje atrybuty. Gracz ma mieć możliwość decydować które dwa atrybuty chce powiększyć w 
stworzeniu.

![image](https://user-images.githubusercontent.com/60191372/210362933-6ca6e135-106c-4dfc-8423-ddc91c979e94.png)
