# Scrabble projekt C++

## Tegijad
Martin Puškini ja Rasmus Valgu ühine C++ projekt.

## Kirjeldus
Esmalt loome töötava Scrabble'i mängu, mis annab igale mängijale klotsid, laseb mängijal lauale sõna asetada, kontrollib, kas see on legaalne, arvutab punktid.
Teiseks lisame mitme mängija toe.
Kolmandaks implementeerime algoritmi, nii et vähemalt üks mängijatest saaks ka arvuti olla. On ka võimalus panna arvuti arvuti vastu mängima.

## Algoritmist
Eesmärk on luua võimalikult kiiresti ja vaevatult töötav mäng, seega esimene algoritm on algselt ilmselt ahne algoritm.
Proovime kasutada DAWG andmestruktuuri, mis on puul põhinev sõnade salvestamise struktuur, kus sarnased sõnad paiknevad "lähestikku".
Sõnad võtame Martini isiklikust sõnastikust.

## Mängust
Lähtume eestikeelse Scrabble'i reeglitest, kus on kõikide sõnade kõik vormid lubatud. Mäng toimub 15x15 mängulaual. Igal mängijal on korraga 7 klotsi. Kotis on 102 klotsi (100 tähte ja 2 tühja klotsi), millest igal on kindel punktide arv. Mängulaual on boonusruudud, mis annavad sellel ruudul olevale sõnale või tähele 2- või 3-kordse punktide summa.
Esimene sõna peab läbima keskmist ruutu. Kõik järgmised sõnad peavad olema ühendatud eelnevalt käidud sõna(de)ga.

Sõnade lauale asetamisel kehtivad reeglid:
1. Kõik sõnad loetakse ülevalt alla või vasakult paremale.
2. Kõik iga käigu lõpus eksisteerivad järjestikused tähtede jadad (ülevalt alla ja vasakult paremale) peavad olema sõnastikus defineeritud sõnad.
3. Ühel käigul peab laduma kõik käidavad tähed ühte ritta või veergu, nii et sinna ritta või veergu tekiks ainult üks sõna, mis võib sisaldada ka juba laual olevaid klotse.

Reaalsuses tuleneb reeglitest, et uusi sõnu saab laduda eelneva sõnaga risti, pikendada, teisele reale kohakuti laduda või moodustada mõni reeglitele vastav kombinatsioon neist.

## Teegid
Graafika jaoks on plaan üritada kasutada Dear ImGuit. Teiseks on plaan kasutada DAWG andmestruktuuri loomiseks spetsiaalset teeki, kus see on juba olemas: https://github.com/chalup/dawggenerator.git. Sellega saadava DAWG-andmestruktuuri lugemiseks ja analüüsimiseks kasutame omaloodud teeki: https://github.com/MartinPuskin/Dawg.git.
