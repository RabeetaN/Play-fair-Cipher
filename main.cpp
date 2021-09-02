#include <iostream>
#include <vector>
using namespace std;

const int BUFFER = 200;

void fillMatrix(char (&)[10], vector<vector<char>> &, vector<char> &);
void  removeSpaces(char *);
void cipherText(vector<pair<char,char>> &, vector<vector<char>> &, vector<char> &);

int main() {
    char key[10];
    char filler[1];
    vector<vector<char>> matrix (5, vector<char> (5));
    vector<char> used;
    char message[BUFFER];
    vector<pair<char,char>> pairs;

    memset(key, '\0', 10);
    cout << "Enter playfair cipher key:\n";
    cin >> key;
    cout << "Enter filler letter:\n";
    cin >> filler[0];

    fillMatrix(key, matrix, used);

    // GET MESSAGE TO ENCRYPT
    cout << "Enter message to encrypt:\n";
    cin.ignore();
    cin.getline(message, BUFFER);
    removeSpaces(message);

    // MAKE THE PAIRS
    for (int a=0; a<strlen(message);) {
        if (message[a] == message[a+1] || message[a+1] == NULL) {
            pairs.push_back(make_pair(message[a], *filler));
            a++;
        }
        else{
            pairs.push_back(make_pair(message[a], message[a + 1]));
            a+=2;
        }
        cout << pairs.back().first << pairs.back().second << endl;
    }
    cipherText(pairs, matrix, used);


}

void fillMatrix(char (&key)[10], vector<vector<char>> &matrix, vector<char> &used){
    char letter = 'a';
    int i = 0, j = 0;
    // PUTTING KEY INTO MATRIX
    for (auto x : key)  {
        if (x != NULL && !(find (used.begin(), used.end(), letter) != used.end()) && x != 'j') {
            if (j < 5) {
                matrix[i][j] = x;
            }
            else {
                i++;
                j = 0;
                matrix[i][j] = x;
            }
            used.push_back(x);
            j++;
        }
    }

    // FILLING THE REST OF THE MATRIX
    for (; i<5; i++){
        for (;j<5; j++){
            while (find (used.begin(), used.end(), letter) != used.end() || letter == 'j'){
                letter++;
            }
            matrix[i][j] = letter;
            used.push_back(letter);
        }
        j = 0;
    }

    // PRINTING MATRIX FOR TESTING
    for (int k=0;k<5;k++) {
        for (int l=0;l<5;l++){
            cout << matrix[k][l] << " ";
        }
        cout << endl;
    }
}

void  removeSpaces(char * c){
    int i = 0, j = 0, cnt = 0;
    while(c[i] != NULL){
        if(c[i] == ' '){
            i++;
            cnt++;
        }
        else{
            c[j] = c[i];
            i++; j++;
        }
    }
    for (int a=cnt; a>0; a--){
        c[strlen(c)-1] = NULL;
    }
}

void cipherText(vector<pair<char,char>> &pairs, vector<vector<char>> &matrix, vector<char> &used){
    // ENCRYPT THE PAIRS
    int frow, fcol, findex, srow,scol, sindex;
    char c;
    vector<char> encrypted;

    for (auto x:pairs){
        auto fit = find(used.begin(), used.end(), x.first);
        auto sit = find(used.begin(), used.end(), x.second);
        if(fit != used.end() && sit != used.end()){
            findex = fit - used.begin(); sindex = sit - used.begin();
            frow = findex/5; srow = sindex/5;
            fcol = findex%5; scol = sindex%5;
            if (frow == srow){
                fcol++; scol++;
                if (fcol == 5){fcol=0;}
                if (scol == 5){scol=0;}
                c = matrix[frow][fcol];
                encrypted.push_back(c);
                c = matrix[srow][scol];
                encrypted.push_back(c);
            }
            else if(fcol == scol){
                frow++; srow++;
                if (frow == 5){frow=0;}
                if (srow == 5){srow=0;}
                c = matrix[frow][fcol];
                encrypted.push_back(c);
                c = matrix[srow][scol];
                encrypted.push_back(c);
            }
            else{
                c = matrix[frow][scol];
                encrypted.push_back(c);
                c = matrix[srow][fcol];
                encrypted.push_back(c);
            }
        }
        //else it means its j
    }

    // PRINT ENCRYPTED MESSAGE
    cout << "Encrypted message:\n";
    for (auto y:encrypted){
        cout << y;
    }
}