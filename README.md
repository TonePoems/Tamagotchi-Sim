# Tamagotchi-Sim
A basic command line Tamagotchi simulator written in C++. My first project of any significance.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The Tamagotchi will track the name, file name 
of the saved state, as well as the basics.
-Age (30-75)
-Hunger (0-4)
-Happiness (0-4)
-Sick (Boolean)
-Character sprite

format the main screen


										    (\_/)
										   (='.'=)  
										   (")_(")


Age: XXX
Fullness:  (XXX )
Happiness: (XX  )	
Your Tamagotich, Name, is healthy/sick.

Name gained a fullness point. / Name is completely full!(if full)
Name gained a happiness point./ Name is completely happy! (if full)

Name lost a fullness point. / Name is starving! You should feed Name a meal.(if 0)
Name lost a happiness point./ Name is completly unhappy! You should play a game with Name or feed Name a snack.(if 0)

1: Feed Name a meal								4: Give Name medicine
2: Feed Name a snack							5: Read instructions
3: Play a game with Name						6: Save and quit game

Please enter your selection: _


The sprites for the character will be:

 (\_/)
(='.'=)  1
(")_(")


  @..@
 (----)
( >__< ) 2
^^ ~~ ^^

  ,__,
 (o.o)
 /),,) 3
  " "
  
  _
 ('<
 /))   4
 /"
  
     __
 ___( o)>
 \ <_. )   5
  `---'
  
  

  
The tamagotchi's responses will come from a related response bank to be randomly selected on prompt 
  
You can feed it, play with it, and give it medicine if it gets sick. Feeding it will increase its â€œfullnessâ€ level, playing with 
it will increase its â€œhappinessâ€ level, and giving it medicine will make it healthy again. The â€œhappinessâ€ and â€œfullnessâ€ levels 
are measured on a scale of 0 through 4 points, 4 points indicating that it is completely full or happy and 0 points meaning that 
it is starving and completely unhappy. Initially, the Tamagotchi has 1 happiness and fullness point each and is healthy.
Instead of simulating Tamagotchi age using days like in the commercial version, your virtual pet will age in â€œcyclesâ€. which will 
be simulated using a giant while loop. Also use a random number generator to govern
whether or not the Tamagotchi loses a happiness and fullness point and whether or not it gets sick during a single cycle. 
More specifically, at the beginning of each cycle, you must first check if the Tamagotchi loses a hunger or happiness point. Each 
of these events has a 50% chance of occurring. Subtract happiness and fullness points for your pet if these events occur. You must 
also check if the Tamagotchi becomes sick -- there is a 20% chance of this occurring. If it does, you must set its sick status. 
Whenever a modification is made, you must also let the user know that the Tamagotchi lost a point in that category or became sick, 
which can be done with a simple print statement.

instructions:
You can feed it, play with it, and give it medicine if it gets sick. Feeding it will increase its â€œfullnessâ€ level, playing with 
it will increase its â€œhappinessâ€ level, and giving it medicine will make it healthy again. The â€œhappinessâ€ and â€œfullnessâ€ levels 
are measured on a scale of 0 through 4 points, 4 points indicating that it is completely full or happy and 0 points meaning that 
it is starving and completely unhappy. Initially, the Tamagotchi has 1 happiness and fullness point each and is healthy.
Instead of simulating Tamagotchi age using days like in the commercial version, your virtual pet will age in â€œcyclesâ€. 
During each cycle, you will have a chance to interact with your Tamagotchi. There are four things one can do to the 
pet, and 2 other options, you must choose which one you would like to do.
You can feed the Tamagotchi one meal per cycle, which increases its total number of fullness points by one. However, if the Tamagotchi 
is already full and you feed it a meal anyway, it will become sick.
You can also feed the Tamagotchi a snack, which will increase its total number of happiness points by one if you are too lazy to play 
with it during that cycle. However, be aware that the Tamagotchi will get sick after every five snacks. Also, you are not allowed to 
exceed the maximum happiness level of 4 points.
You can also play a game with the Tamagotchi, which will increase its current happiness points by one.
Finally, you can give your Tamagotchi medicine if it gets sick, which will make it healthy again. Again, you cannot give your Tamagotchi medicine if it is not sick.



//set up random responses
vector <string> quoteChoice(4);
int randomQuote;
srand(time(NULL));

//specify quotes
quoteChoice.resize(4);
quoteChoice[0] = "";
quoteChoice[1] = "";
quoteChoice[2] = "";
quoteChoice[3] = "";

randomQuote = rand() % 4;

cout << quoteChoice[randomQuote] << endl;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
