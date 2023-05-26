#include <iostream>

using namespace std;


void printArray(int arr[],int n){
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void Permutation(int arr[], int index[], int n){
    int temp[n];
    for (int i=0; i<n; i++)
        temp[i] = arr[index[i]-1];
    for (int i=0; i<n; i++)
        arr[i] = temp[i];
    }

void Split(int arr[], int n, int *l, int *r){
    for(int i=0;i<n/2;i++)
        l[i] = arr[i];
    for(int j=0,i=n/2;i<n;i++,j++)
        r[j] = arr[i];
}

void combine(int arr1[], int arr2[], int *arr3, int n){
    for (int i=0;i<n/2;i++)
        arr3[i]=arr1[i];
    for (int i=n/2,j=0;i<n;i++,j++)
        arr3[i]=arr2[j];
}

void leftRotate(int arr[], int d, int n){
    int temp[d];
    for (int i=0; i<d; i++)
        temp[i] = arr[i];
    for (int i = 0; i < n-d; i++)
        arr[i] = arr[i+d];
    for (int i=n-d,j=0; i<n; i++,j++)
        arr[i]=temp[j];
}


class KeyGeneration {
    private:
    int P10_rule[10] = {3,5,2,7,4,10,1,9,8,6};
    int P8_rule[8] = {6,3,7,4,8,5,10,9};
    int tempLeft[5]={};
    int tempRight[5]={};
    
    public:
    KeyGeneration(){}
    void key(int masterKey[], int *k1, int *k2){
        //Apply P10
        Permutation(masterKey,P10_rule,10);
            cout<<endl;
            cout<<"After P10 Permutation"<<endl;
            printArray(masterKey,10);
            cout<<endl;
        //Split
        Split(masterKey,10,tempLeft,tempRight);
            cout<<"After split"<<endl;
            cout<<"l = ";
            printArray(tempLeft,5);
            cout<<"r = " ;
            printArray(tempRight,5);
            cout<<endl;
        //Left Shift 1-bit
            leftRotate(tempLeft,1,5);
            leftRotate(tempRight,1,5);
            cout<<"After LeftShift - 1"<<endl;
            cout<<"l = ";
            printArray(tempLeft,5);
            cout<<"r = ";
            printArray(tempRight,5);
            cout<<endl;
        //Apply P8
            combine(tempLeft,tempRight,masterKey,10);
            Permutation(masterKey,P8_rule,10);
            cout<<"After P8, Subkey - 1 "<<endl;
            for(int i=0;i<8;i++)
            k1[i]=masterKey[i];
            printArray(k1,8);
            cout<<endl;
        //Left Shift 2-b,rs to step B
            leftRotate(tempLeft,2,5);
            leftRotate(tempRight,2,5);
            cout<<"After LeftShift - 2"<<endl;
            cout<<"l = ";
            printArray(tempLeft,5);
            cout<<"r = ";
            printArray(tempRight,5);
            cout<<endl;
        //Apply P8
            combine(tempLeft,tempRight,masterKey,10);
            Permutation(masterKey,P8_rule,10);
            cout<<"After P8, Subkey - 2"<<endl;
            for(int i=0;i<8;i++)
            k2[i]=masterKey[i];
            printArray(k2,8);
    }
};

int main(){
    char input;
    int arr[8]={};
    int masterKey[10]={};
    int k1[8]={},k2[8]={};
    int fk1[8] = {};
    cout<<"Enter 10-bit Master Key (using space)"<<endl;
    for(int i=0;i<10;i++){
        cin>>masterKey[i];
    }
    KeyGeneration k;
    k.key(masterKey,k1,k2);
    return 0;
}