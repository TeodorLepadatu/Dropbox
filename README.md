# Dropbox

Acesta este un shell personalizat care expune funcționalitățile utilitarului `dbxcli` pentru interacțiunea cu Dropbox și face legătura cu sistemul de fișiere local al utilizatorului. Aplicația permite executarea comenzilor `dbxcli` în cadrul unui mediu controlat, în care utilizatorul poate efectua operațiuni specifice asupra fișierelor și directoarelor stocate pe Dropbox și în sistemul local.

## Funcționalități disponibile

1. **`cp`** - Copiere fișiere între Dropbox și sistemul local:
   - Exemplu de utilizare: 
     ```
     >> cp /cale/catre/fisier_local /cale/catre/fisier_destinatie
     ```
   - Copierea unui fișier sau a unui set de fișiere între Dropbox și sistemul local este posibilă folosind această comandă.

2. **`mv`** - Mutare fișiere între Dropbox și sistemul local:
   - Exemplu de utilizare:
     ```
     >> mv /cale/catre/fisier_local /cale/catre/fisier_destinatie
     ```
   - Comanda `mv` poate fi utilizată pentru a muta fișiere și directoare între Dropbox și sistemul local.

3. **`mkdir`** - Creare de directoare în Dropbox:
   - Exemplu de utilizare:
     ```
     >> mkdir /cale/catre/director
     ```
   - Creează un nou director pe Dropbox.

4. **`rm`** - Ștergere fișiere din Dropbox:
   - Exemplu de utilizare:
     ```
     >> rm /cale/catre/fisier
     ```
   - Permite ștergerea fișierelor din Dropbox.

5. **`ls`** - Listarea fișierelor din Dropbox:
   - Exemplu de utilizare:
     ```
     >> ls /cale/catre/director
     ```
   - Afișează fișierele și directoarele dintr-o locație specificată din Dropbox.

6. **`search`** - Căutarea fișierelor în Dropbox folosind un termen specific:
   - Exemplu de utilizare:
     ```
     >> search "termen_căutare" /cale/catre/director
     ```
   - Căutarea fișierelor pe Dropbox care corespund unui termen specificat.

## Cum funcționează

Aplicația pornește un shell interactiv în care utilizatorul poate introduce comenzi. Fiecare comandă este procesată și, în funcție de comanda introdusă, sunt efectuate acțiuni asupra Dropbox sau a sistemului de fișiere local. 

Utilizatorul poate rula următoarele comenzi:
- **Comenzi de gestionare fișiere**: copiere, mutare, crearea de directoare și ștergere.
- **Căutare fișiere**: utilizând comanda `search`, utilizatorul poate căuta fișiere folosind un termen specificat.
- **Comenzi de vizualizare**: listarea fișierelor dintr-un director specificat.

Aplicația va lansa procesele corespunzătoare pentru fiecare comandă și va aștepta ca acestea să fie finalizate înainte de a reveni la promptul principal.

## Cum să folosești aplicația

1. **Clonează sau descarcă proiectul:**
   - Descarcă sursa aplicației pe mașina ta.
   
2. **Construirea aplicației:**
   - Compilează aplicația folosind un compilator C standard:
     ```
     gcc -o db db.c
     ```

3. **Execută aplicația:**
   - Rularea aplicației poate fi făcută simplu prin:
     ```
     ./db
     ```

4. **Interacțiunea cu shell-ul:**
   - După ce aplicația este pornită, vei vedea promptul `>>`. Aici, poți introduce comenzile disponibile pentru a interacționa cu Dropbox și sistemul local.

## Exemple de utilizare

### Copiere fișier din Dropbox în sistemul local:
cp /Dropbox/fisier.txt /home/utilizator/fisier_local.txt


### Mutare fișier din sistemul local în Dropbox:
mv /home/utilizator/fisier_local.txt /Dropbox/


### Creare director pe Dropbox:
mkdir /Dropbox/nou_director

### Listare fișiere dintr-un director pe Dropbox:
ls /Dropbox/


### Căutare fișier în Dropbox:
search "document.txt" /Dropbox/

### Ștergere fișier din Dropbox:
rm /Dropbox/fisier_de_șters.txt


## Considerații

- Este necesar ca aplicația `dbxcli` să fie instalată pe sistemul tău pentru ca comenzile să funcționeze corect.
- Asigură-te că ai permisiunile corespunzătoare pentru a accesa și modifica fișierele pe Dropbox.
- Aplicația folosește funcții de bază ale shell-ului Unix (`execve`, `fork`, `wait`), astfel încât să poată lansa comenzi și să aștepte ca acestea să se termine.
