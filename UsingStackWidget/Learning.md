In this project we have made two screen.
1) Main screen
2) Second screen

We want to open second screen after pressing button in main screen.
To achieve this we have used stacked widget.

We insert second page widget in main screen page stack widget.
For that we firstly create a instance for second page if it is not available.
We created second page instance in its cpp file.

<h4><b>NOTE:</b></h4> Whatever variable or function we need to call in its cpp file we need to make it in header file. <br> 
  But if we need to make variable which is going to be used in that particular function (local variable) it is not needed to be declared in header file.
<br><br>

  #SecondScreen.h<br>
```
public:
    static SecondScreen * SecondScreen_instance;
    static SecondScreen * SecondScreen_current_instance();
```
In above code we are creeating a pointer variable and function <br><br>

#SecondScreen.cpp<br>
```
SecondScreen * SecondScreen::SecondScreen_instance=0;
SecondScreen * SecondScreen::SecondScreen_current_instance()
{
    if (!SecondScreen::SecondScreen_instance)
    {
        SecondScreen::SecondScreen_instance = new SecondScreen;
    }
    return SecondScreen::SecondScreen_instance;
}
```
In above code we are initiallizing variable SecondScreen_instance by 0 so there will be nothing in it.<br>
Then we have created a function to create a new instance which having all parameters of SecondScreen.<br>
The word "new"  creates a new instance of secondscreen.<br>

<b>What is use of pointer?</b><br>
pointer is basically used for storing address.<br>
In our case we are using it to store address of SecondScreen so that we can access all its public variable, signals and functions.<br>

