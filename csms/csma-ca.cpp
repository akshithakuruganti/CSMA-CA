#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>
#include <math.h>
using namespace std;

int seconds = 5;
int K_attempt = 0, Kmax = 5; //number of K attempt = 5
int AckMethod,ack;
bool loop = false;
int F_bit[8];
char Rack;

void displayClock()
{
    cout << setfill(' ') << setw(29);
    cout << setfill('0') << setw(2) << seconds << " sec |" << endl;
}

void waitIFS(){
    cout <<"TIMER: \n";
        while (true) {
             
            // display the timer
            
            displayClock();
     
            // sleep system call to sleep
            // for 1 second
            usleep(500000);
     
            // increment seconds
            seconds--;
     
            // if seconds reaches 60
            if (seconds == 0) {
                seconds = 5;
                break;
            }
        }
    return;
}

void ack_yes_no(){
    if (K_attempt < Kmax) {
        cout <<endl;
        cout << "Received Acknowlegment? (y/n) "<<endl;
        cin >> Rack;
        cout <<endl;
    }
    
    if (Rack == 'y' || Rack == 'Y') {
        ack = 1;
        if (ack == 1) {
            cout << "Acknowledgement Received"<<endl;
            cout << "Success! "<<endl;
            
        }
        else if (ack == 0){
            cout<< "No Acknowledgement Received"<<endl;
            
            }
        
    }
    else if (Rack == 'n' || Rack == 'N') {
        ack = 0;
        if (ack == 1) {
            cout << "Acknowledgement Received"<<endl;
            cout << "Success! "<<endl;
        }
        else if (ack == 0){
            cout<< "No Acknowledgement Received"<<endl;
            
            }
        
    }
    else{
        cout << "Error: Invalid Syntax"<<endl;
        ack_yes_no();
    }
    
}

void AutoAck(){
    srand((unsigned) time(0));
    ack = (rand() % 2 );
    cout << ack <<endl;
    cout <<endl;
    if (ack == 1 || ack == 0) {
        if (ack == 1) {
            cout << "Acknowledgement Received"<<endl;
            cout << "Success! "<<endl;
        }
        else if (ack == 0){
            cout<< "No Acknowledgement Received"<<endl;
            }
        
        }
    }
    

void goMethod(){
    if (AckMethod == 1) {
        AutoAck();
    }
    else if (AckMethod == 2){
        ack_yes_no();
    }
}

void WaitAck(){
    cout <<"Receiving ACK... \n";
        while (true) {
             
            // display the timer
            
            displayClock();
     
            // sleep system call to sleep
            // for 0.5 second
            usleep(500000);
     
            // increment seconds
            seconds--;
     
            // if seconds reaches 60
            if (seconds == 0) {
                seconds = 5;
                break;
            }
        }
    goMethod();
}

void sendFrame(){
    cout<<endl;
    cout << "Sending Frame..." <<endl;
    usleep(500000);
    cout <<endl;
    if (loop == false) {
        srand((unsigned) time(0));
        for(int i=0;i<8;i++){
            F_bit[i] = (rand() % 2 );
        }
    }
    cout <<endl;
    cout << F_bit[7]<<" ";
    usleep(500000);
    cout << F_bit[6]<<" ";
    usleep(500000);
    cout << F_bit[5]<<" ";
    usleep(500000);
    cout << F_bit[4]<<" ";
    usleep(500000);
    cout << F_bit[3]<<" ";
    usleep(500000);
    cout << F_bit[2]<<" ";
    usleep(500000);
    cout << F_bit[1]<<" ";
    usleep(500000);
    cout << F_bit[0]<<" ";
    cout <<endl;
    
    WaitAck();
}

void ContentionWindow(){
    srand((unsigned) time(0));
    int randomNumber,R,K;
    cout << endl;
    cout << "Key in number of slot, K\n";
    cin >> K;
    double x = 2, y = K;
    R = pow(x,y)-1;
    cout <<endl;
    cout <<"Random number in ";
    cout << R <<endl;
    cout <<endl;
        randomNumber = (rand() % R);
    sleep(1);
    cout << randomNumber;
    if (randomNumber == 0) {
        randomNumber++;
    }
    cout << " slots selected"<<endl;
    usleep(500000);
    while (true) {
        if (randomNumber > 0) {
            
            randomNumber--;
            cout << randomNumber<<endl;
            usleep(500000);
            if (randomNumber == 0) {
                randomNumber = (rand() % R);
                break;
            }
        }
       
    }
    
    sendFrame();
}


void FrameReady(){
    char frame;
    cout <<endl;
    cout << "Is the Frame Ready? (y/n)\n";
    cin >> frame;
    //cout << frame; //For Testing & Debug
    cout <<endl;
    if (frame == 'Y' || frame == 'y') {
        waitIFS();
        cout <<endl;
        cout << "Is the Frame Still Ready? (y/n)\n";
        cin >> frame;
        //cout << frame<<endl; //For Testing & Debug
        if (frame == 'Y' || frame == 'y') {
            cout <<endl;
            waitIFS();
            ContentionWindow();
            return;
        }
        else if (frame == 'N' || frame == 'n'){
            cout <<endl;
            waitIFS();
            FrameReady();
            return;
        }
        else{
            cout<<endl;
            cout << "Error: Invalid Syntax" <<endl;
            FrameReady();
        }
        return;
    }
    else if (frame == 'N' || frame == 'n'){
        waitIFS();
        FrameReady();
        return;
    }
    else{
        cout<<endl;
        cout << "Error: Invalid Syntax" <<endl;
        FrameReady();
    }
}


void chooseAckMethod(){
    cout << "Press 1 to use random generator"<<endl;
    cout << "Press 2 to input the acknowldgement "<<endl;
    cin >> AckMethod;
    if (AckMethod == 1 || AckMethod == 2 ) {
        return;
    }
    else {
        cout <<AckMethod;
        cout << "Error: Invalid Input "<<endl;
        chooseAckMethod();
  
    }
    
}





int main(int argc, const char * argv[]) {
    
    chooseAckMethod();
    FrameReady();
    if (ack == 0) {
        while (K_attempt<Kmax) {
            K_attempt++;
            cout <<endl;
            cout<<" attempt = "<< K_attempt<< endl;
            cout<<endl;
            waitIFS();
            loop = true;
            FrameReady();
            if (ack == 1) {
                break;
            }
        }
        
        if (K_attempt>=Kmax) {
            cout << "Abort";
            usleep(500000);
            cout << ".";
            usleep(500000);
            cout << ".";
            usleep(500000);
            cout << ".";
            usleep(500000);
            cout << ".";
            usleep(500000);
            cout << ".";
            usleep(500000);
            cout << ".";
            return 0;
        }
    }
    else
    return 0;
}
