#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>

using namespace std;


long double sta(string str){

char mod;
int i, decc = 0, decimal = 0; //decc is the decimal counter, whereas decimal shows when and if decimals are being input.
double sta = 0;       //sta is a, still unknown, double that will take the value of
		      //the number from the input, converted to meters.

//Checking for errors happens by returning a negative value.
//If a negative value is returned, an error has occured.

if(str.length() < 2){
  cout << "Error: minimum length is 2 (number, multiple of meter)\n";
  return -1;
}

//In case the last character isn't m, then there is no point proceeding, so we check for that first.

if(str[str.length() - 1] != 'm' ){
  cout << "Error: expected input in meter (m) multiple \n";
  return -1;
}

//If only 2 characters are input, we check for every possible outcome seperately
//from the following for loop, as that is designed for strings with length >= 3.
if(str.length() == 2){
  if(str[0] == '.')
   return 0;
  else if(str[0] <= 57 && str[0] >= 48)
   return (int) str[0] - '0';
  else{
   cout << "Error: please enter DIGITS and '.' only, followed by meter multiple\n";
   return -1;
  }
}

//In this for loop we convert the number from a string to a double float, digit by digit.
  for(i = 0; i <= (str.length() - 3); i++){

//This check is here to keep track of how many digits there are after the decimal point.
   if(decimal == 1)
     decc++;

//This 'if' checks for a decimal point '.', and that only one has been input, else we have an error.
   if(str[i] == '.'){
    if(decimal == 0){
     decc = 0;
     decimal = 1;
     continue;
    }
    else
     cout << "Error: More than one '.' in the input. Please enter only one\n";
     return -1;
   }

//This check is to ensure nothing except digits and '.'s are input.
   if((str[i] < 48 || str[i] > 57) && str[i] != '.'){
     cout << "Error: please enter DIGITS and '.' only, followed by meter multiple\n";
     return -1;
   }
//The conversion happens by using the fact that, in ASCII,
//The integer value of a digit literal is their actual int value + 48, which is the value of '0'.
   sta = 10*sta + ((int) str[i] - '0');
  }

//if the last two members of the input string are a digit and 'm',
//then the digit is also converted and the double is returned as is, since the input is in meters.
if(str[str.length() - 2] >= 48 && str[str.length() - 2] <= 57 && str[str.length() - 1] == 'm'){
  sta = 10*sta + ((int) str[i] - '0');
  if(decimal)
    sta /= pow(10,decc + 1);

  return sta;
}

//according to how many digits after the decimal point we have,
//we divide the double by the appropriate power of 10.

sta /= pow(10,decc);

//str[str.length() - 1], assuming we have reached this far without errors,
//has the value of the meter modifier.
mod = str[str.length() - 2];

if(mod == '.' && !decimal)
  sta /= 1;

else if(mod == '.' && decimal){
  cout << "Error: More than one '.' in the input. Please enter only one\n";
  return -1;
}

 switch(mod) {
  case 'p':
    sta /= pow(10,12);
    break;
  case 'n':
    sta /= pow(10,9);
    break;
  case 'u':
    sta /= pow(10,6);
    break;
  case 'm':
    sta /= pow(10,3);
    break;
  case 'c':
    sta /= 100;
    break;
  case 'd':
    sta /= 10;
    break;
  case 'k':
    sta *= 1000;
    break;
  case 'M':
    sta *= pow(10,6);
    break;
  case 'G':
    sta*= pow(10,9);
    break;
  case 'T':
    sta *= pow(10,12);
    break;
  default:
    cout << "Error: this type of meter multiple \"" << str[str.length() - 2] << "\" doesn't exist\n";
    return -1;
 }

//If the modifier is invalid, an error will occur.

//Otherwise, the converted, final value is returned to be output.
return sta;
}


int main(){

//Nonst = Nonstandard, essentially the string with the value to be converted.
string Nonst;
double standard = 0;

cout << "Please enter length to be converted (exit with 'q')\n";

getline(cin, Nonst);

  while(Nonst != "q"){

     standard = sta(Nonst);

//If the value standard is negative, that means an error occured.
     if(standard >= 0)
      cout << scientific << standard << "m\n";

     getline(cin,Nonst);
  }

return 0;
}
