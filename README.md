# Card-Match-Game
1) Purpose Of the Game
The purpose of this project is to write a game called CardMatch using QTCreator and Cpp. The
game’s main objective is to match the same fruits by finding each other without exceeding the
number of tries remaining which is 50. If you exceed the number of tries you will lose the game.
If you can match all the pairs within 50 tries you win the game. Your score will increase by 1
with every successful match. If you can’t match the right cards those blocks will be hidden
again and your number of tries left will decreas by 1. By every click to New Game Button you
will start a new game with new shuffled cards and your score and number of tries left will reset
to their initial numbers.
2) Program Execution
You can start the game in QT Creator by running the code. After that you can click the New
Game Button to start the CardMatch Game.
3) Explanations Of The Code
CardMatch Project 3 3
QString fruit[30] = {
"Apple", "Banana", "Orange", "Grapes", "Strawberry", "Mango",
"Watermelon", "Pineapple", "Cherry", "Kiwi", "Pear", "Peach",
"Plum", "Blueberry", "Raspberry" , "Apple", "Banana", "Orange", "Grapes", "Strawberry", "Mango",
"Watermelon", "Pineapple", "Cherry", "Kiwi", "Pear", "Peach",
"Plum", "Blueberry", "Raspberry"};
int Score;
int Tries=50;
The code above includes an array called fruit which contains the names of 15 different fruits,
each of which is duplicated in the list to create 30 total elements in the array. The game uses
this array to create pairs of cards (blocks in our game) with matching fruit texts. The Score and
Tries variables are also defined in the code; Score keeps track of the player's score (it is
incremented by 1 with each successful match) , while Tries keeps track of the number of
remaining attempts the player has to match all the pairs of cards. The game ends if the player
runs out of tries before all the pairs are matched.
if (button->isChecked()) {
button->setText(fruit[button->property("id").toInt()]);
qDebug() << "Clicked button with item number:" << button->property("id").toInt();
button->setDisabled(true);
}
The second code snippet provided shows an if statement that is called when a button is
clicked. If the button is checked (clicked), the text of the button is set to the fruit name from “”
corresponding to the button's id property. Finally, the button is disabled so that it cannot be
clicked again until the other matched pair is selected.
int count = 0;
for (int i = 0; i < gridLayout->count(); ++i) {
QPushButton* button = qobject_cast<QPushButton*>(gridLayout->itemAt(i)->widget());
if (button) {
if (button->isChecked()) {
count++;
}
}
}
CardMatch Project 3 4
This code snippet provided is a for loop that iterates through all the items in the gridLayout .
For each item, it tries to cast it to a QPushButton . If the cast is successful, it checks if the button
is checked (clicked). If the button is checked, it increments the count variable. This count
variable keeps track of how many buttons are currently checked. And after one try of pair
matching it reaches 2 count.
If the count is 2 we understand that 2 button is clicked so it means that we chosed 2 fruits now
it is time to check if they are a match.
With 2 for loops we find 2 clicked buttons now evaluations starts with the code snippet below
if (button->text() == button2->text()) {
Score = Score + 1;
QString ScoreString = QString::number(Score);
ScoreText->setText(ScoreString);
if(Score == 15) {
QMessageBox::information(this, "Game Over", "You have won the game");
}
button->setChecked(false);
button2->setChecked(false);
button->setDisabled(true);
button2->setDisabled(true);
}
If the button texts are equal meaning that the fruits are a match we increment the score by one
and disable the buttons of these fruits so that they are not further clickable. Also if the score is
15 by getting this pair match it means you won and it ends the game.
Else if it is not a match:
else {
qDebug() << "Clicked button with item number:" << button->property("id").toInt();
Tries = Tries -1;
qDebug() << "try :" << Tries;
QString TriesString = QString::number(Tries);
TriesText->setText(TriesString);
if(Tries == 0) {
flag = true;
QMessageBox::information(this, "Game Over", "You have no more tries left");
for (int i = 0; i < gridLayout->count(); ++i) {
QPushButton* button = qobject_cast<QPushButton*>(gridLayout->itemAt(i)->widget());
if (button) {
button->setDisabled(true);
}
}
}
CardMatch Project 3 5
QTimer::singleShot(500, [button, button2]() {
button->setChecked(false);
button2->setChecked(false);
button->setText("");
button2->setText("");
});
if(flag == false) {
button->setDisabled(false);
button2->setDisabled(false);
}
}
The else case in the code is executed when the two clicked buttons do not match. In this case,
the number of remaining attempts is reduced by 1, and the updated value is displayed in the
TriesText field. If the player has no remaining tries, the flag variable is set to true meaning
that the game has ended because you have no more tries left, a message is displayed
informing the player that the game is over, and all buttons are disabled. If the player has
remaining tries, the buttons are unchecked and again choosable and their text is set to “” after a
delay of 500 milliseconds, and the buttons are re-enabled.
for (int i = 0; i < 30; i++) {
int random = rand() % 30;
QString temp = fruit[i];
fruit[i] = fruit[random];
fruit[random] = temp;
}
This for loop shuffles the cards with every new game start.
for (int i = 0; i < gridLayout->count(); ++i) {
qDebug() << fruit[i];
QPushButton* button = qobject_cast<QPushButton*>(gridLayout->itemAt(i)->widget());
if (button) {
disconnect(button, &QPushButton::clicked, this, &MainWindow::handleButtonClicked);
}
}
// Make the buttons checkable and connect the clicked signal to the handleButtonClicked slot
for (int i = 0; i < gridLayout->count(); ++i) {
QPushButton* button = qobject_cast<QPushButton*>(gridLayout->itemAt(i)->widget());
if (button) {
button->setEnabled(true);
button->setCheckable(true);
CardMatch Project 3 6
button->setChecked(false);
button->setEnabled(true);
button->setText("");
button->setProperty("id", i );
connect(button, &QPushButton::clicked, this, &MainWindow::handleButtonClicked);
}
}
We attain the needed fields to all the buttons of the fruits meaning the cards that we created in
Qt design. These fields are according to the new game state. So they are not checked, enabled
and their text left blank to hid the fruit. We attain also the id of the block to this button.
