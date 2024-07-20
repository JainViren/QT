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

Now going further to our task which is on clicking button we need to open secondscreen.<br>
For this we need to insert SecondScreen instance into second page of stack-widget.<br>
1) This can be achieved by two method either by inserting SecondScreen instance only when button is pressed.
2) Inserting when app load and switch to that page when button is clicked.

In this we are going to follow second one.<br>
#application.cpp<br>
```
    ui->setupUi(this);
    // ADD USER CODE HERE
    ui->AppStack->setCurrentIndex(0);
    ui->AppStack->insertWidget(2,SecondScreen::SecondScreen_current_instance());
```
In above code firstly we are setting stack to page 0 using setCurrentIndex(0) then inserting our SecondScreen instance at page 2.<br>
we have used 2 and stack counting is started from 0 so in real life it is at page 3.<br>
<h4><b>NOTE:</b></h4>
1) Inserting index will not show that page.<br>
2) If you insert your page at position 3 and there any only 1 current page then it will create other blank pages.<br>
3) Inserting page at n position will shift all page from n position to n+1<br>

Coming to our point now we need to give button a function to show SecondScreen page instance<br>
#application.cpp<br>

```
void Application::on_pushButton_clicked()
{

    ui->AppStack->setCurrentIndex(2);

}
```

<b> What is signal and slot?</b><br>
Signal and slots are used to connect two functions from different parent class.<br>
Lets go to our example for simplicity.<br>
when we want to switch from main frame to secondscreen then we just need give button a function.<br>
But when we need need to go back to main window and give button in secondscreen and give it a function then it will not work.<br>
Reason is that our stack widget is in main parent class but button is in second screen parent class.<br>
As there is no any stack widget it will not do anything<br>
So to handle this situation we use signal and slot.<br>

<h4><b>How it will work?</b></h4><br>
We need to connect SecondScreen with main screen using signal, slot and connect.<br>
We will emmit signal on pushing button. This signal will be connecting to main frame using slots.<br>
For that we need to make signals in header file of secondscreen and public slot in application header file and connect them in application.cpp file using connect.<br>
#secondscree.h

```
signals:
    void test_1();
```
#secondscree.cpp

```
void SecondScreen::on_pushButton_released()
{

    emit test_1();
}
```
#application.h

```
public slots:
    void Recieve();
```
#application.cpp

```
 connect(SecondScreen::SecondScreen_current_instance(), SIGNAL(test_1()), this, SLOT(Recieve()));

void Application::Recieve()
{
    qDebug()<<"on";
    ui->AppStack->setCurrentIndex(0);



}
```
In above code it is clear that we are creating signals then emit it and connect them in application and do function using slots.<br>

For learning more we are taking one more example of sharing data using signal and slot SendingSignal() and Recieving().<br>

<h4><b>NOTE:</b></h4><br>
In this example we are checking for availability of instance of second screen so it is not possible to make multiple pages.<br>
It means if you will insert this instance at 2nd position and later on if you want same screen in position 2 as well as in position 3.<br>
for achieving this if you firstly enter it position 2 and then 3 then the last will be counted only.<br>
Means your instance will be at position 3 only and will remove from position 2. <br>
For that you have to make new instance.


