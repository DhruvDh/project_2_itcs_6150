

/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <stdlib.h>

using namespace std;

//Global variables:

int n;
int BoardPos[100];
int BoardCopy[100];
int initialPos[100];

// for steepest-ascent
int Success1 = 0;
int Failure1 = 0;

// for with side Moves
int Success2 = 0;
int Failure2 = 0;

// randomRestart
int Success3 = 0;
int Failure3 = 0;

//randomRestart with SideMove
int Success4 = 0;
int Failure4 = 0;

int previousSuccess1 = 0;
int previousSuccess2 = 0;

int numberOfRuns = 300;

int successSteps1 = 0;
int successSteps2 = 0;

int failureSteps1 = 0;
int failureSteps2 = 0;

int randomRestartCount = 0;
int randomRestartSideMoveCount = 0;

int randomRestartSteps = 0;
int randomRestartStepsSideMove = 0;

int numberOfCalls3 = 0;
int numberOfCalls4 = 0;

void copyArray()
{
    for (int i = 0; i < n; i++)
        BoardPos[i] = BoardCopy[i];
}
void initializeBoard()
{
    for (int i = 0; i < n; i++)
    {
        BoardCopy[i] = initialPos[i];
        BoardPos[i] = initialPos[i];
    }
}
void printArray()
{
    cout << "\n\n";
    for (int i = 0; i < n; i++)
        cout << BoardPos[i] << " ";
}

int calculateH()
{
    int h = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (BoardPos[i] == BoardPos[j]) //check if in the same row
                h++;
            if ((BoardPos[i] == BoardPos[j] - (j - i)) || (BoardPos[i] == BoardPos[j] + (j - i))) //check for diagonal elements
                h++;
        }
    }
    return h;
}

void printSuccessFailure()
{

    printf("\n===================================");
    printf("\nSteepest-ascent");
    printf("\n===================================");
    printf("\nSuccess:%i \nFailure:%i ", Success1, Failure1);
    cout << "\nAverage Success steps:" << (int)(float)successSteps1 / Success1 << "\nAverage Failure steps:" << (int)(float)failureSteps1 / Failure1;
    cout << "\nSuccess rate: " << (float)Success1 / numberOfRuns * 100 << "% \nFailure rate:" << (float)Failure1 / numberOfRuns * 100 << "%";

    printf("\n\n===================================");
    printf("\nHill climb With side Move");
    printf("\n===================================");
    printf("\nSuccess:%i \nFailure:%i ", Success2, Failure2);
    if (Failure2 == 0)
        cout << "\nAverage Success steps:" << (int)(float)successSteps2 / Success2 << "\nAverage Failure steps:" << 0;
    else
        cout << "\nAverage Success steps:" << (int)(float)successSteps2 / Success2 << "\nAverage Failure steps:" << (int)(float)failureSteps2 / Failure2;
    cout << "\nSuccess rate: " << (float)Success2 / numberOfRuns * 100 << "% \nFailure rate:" << (float)Failure2 / numberOfRuns * 100 << "%";

    printf("\n\n===================================");
    printf("\nRandom Restart");
    printf("\n===================================");
    //printf("\nSuccess:%i \nFailure:%i ",Success3,Failure3);
    cout << "\nAverage Restart Required:" << (int)(float)randomRestartCount / numberOfRuns;
    cout << "\nAverage steps:" << (int)(float)randomRestartSteps / numberOfCalls3;
    //cout<<"\nSuccess rate: "<< (float) Success3/numberOfRuns *100<<"% \nFailure rate:"<<(float) Failure3/numberOfRuns *100<<"%";

    printf("\n\n===================================");
    printf("\nRandom Restart with Side Move");
    printf("\n===================================");
    //printf("\nSuccess:%i \nFailure:%i ",Success4,Failure4);
    if (numberOfRuns == 0)
        cout << "\nAverage Restart Required:" << 0; //(int)(float)randomRestartSideMoveCount/numberOfRuns;
    else
        cout << "\nAverage Restart Required:" << (int)(float)randomRestartSideMoveCount / numberOfRuns;
    if (numberOfCalls4 == 0)
        cout << "\nAverage steps:" << randomRestartStepsSideMove; //(int)(float)randomRestartStepsSideMove/numberOfCalls4;
    else
        cout << "\nAverage steps:" << (int)(float)randomRestartStepsSideMove / numberOfCalls4;
    //cout<<"\nSuccess rate: "<< (float) Success4/numberOfRuns *100<<"% \nFailure rate:"<<(float) Failure4/numberOfRuns *100<<"%";
}

void hillClimbingSteep() // Consider ONLY the best move     //Example : [2 1 3 0]- failure  [2 0 3 0]-success
{
    int h = calculateH();
    int minH = h;
    //cout<<"\ninitial H val: "<<h;

    int nextPossibleMove[n];
    int k = 12;
    int terminate = 0;
    int loop = 0;
    while (h > 0 && terminate == 0) //1 while loop generates all the possible successors of the current node and chooses the best one
    {
        loop++;
        int flag = 0;
        for (int i = 0; i < n; i++) //for each col
        {
            for (int j = 0; j < n; j++) // each row of col
            {

                if (j != BoardPos[i])
                {
                    BoardPos[i] = j;
                    //printArray();
                    h = calculateH(); //update H value
                    //cout<<"\n"<<h;

                    if (h < minH)
                    {
                        minH = h;
                        flag = 1;
                        for (int i = 0; i < n; i++)
                            nextPossibleMove[i] = BoardPos[i];
                    }
                }
                copyArray();
            }
            //printf("\n===========================");
        }

        //printf("\n===========================");
        if (flag == 0) //(minH<h || minH==h)
        {
            terminate = 1;
            //printf("\nhere");
        }
        else
        {
            //printf("\nmin H val:%i",minH);
            //printf("\nNext move: ");
            //for(int i=0;i<n;i++)
            //cout<<nextPossibleMove[i]<<" " ;

            //change current BoardPos to best move
            h = minH;
            for (int i = 0; i < n; i++)
            {
                BoardPos[i] = nextPossibleMove[i];
                BoardCopy[i] = nextPossibleMove[i];
            }
            k--;
        }
    }
    if (terminate == 1)
    {
        //printf("\nfailed to find solution");
        failureSteps1 += loop;
        Failure1++;
    }
    else if (h == 0)
    {
        //printf("\nSuccess!");
        successSteps1 += loop;
        Success1++;
    }
}

void hillClimbingSideMove() //consider equal or less than H value with Max allowed side Moves:100
{
    int h = calculateH();
    int minH = h;
    //cout<<"\ninitial H val: "<<h;

    int nextPossibleMove[n];
    int k = 12;
    int sidewaysCount = 0;
    int loop = 0;

    int previousH = h;
    int previousSidewayH = 0;
    while (h > 0 && sidewaysCount < 100) //Allow Max of 100 side Moves
    {
        loop++;
        int flag = 0;
        for (int i = 0; i < n; i++) //for each col
        {
            for (int j = 0; j < n; j++) // each row of col
            {

                if (j != BoardPos[i])
                {
                    BoardPos[i] = j;
                    //printArray();
                    h = calculateH(); //update H value
                    //cout<<"\n"<<h;

                    if (h < minH)
                    {
                        minH = h;
                        flag = 1;
                        for (int i = 0; i < n; i++)
                            nextPossibleMove[i] = BoardPos[i];
                    }
                    else if (flag == 0 && h == previousH) //h==minH)
                    {
                        minH = h;
                        for (int i = 0; i < n; i++)
                            nextPossibleMove[i] = BoardPos[i];
                    }
                }
                copyArray();
            }
            //printf("\n===========================");
        }

        //printf("\n===========================");
        //printf("\nmin H val:%i",minH);
        //printf("\nNext move: ");
        //for(int i=0;i<n;i++)
        //cout<<nextPossibleMove[i]<<" " ;

        //update sidewaysCount if sideWay move was allowed
        if (flag == 0 && minH == previousH)
        {
            if (previousSidewayH == minH) //update sidewaysCount for that particular H value
                sidewaysCount++;
            else
            {
                previousSidewayH = minH; //for new H value update previousSidewayH and initialize sidewaysCount to 1
                sidewaysCount = 1;
            }
        }
        //change current BoardPos to best move
        h = minH;
        previousH = minH;
        for (int i = 0; i < n; i++)
        {
            BoardPos[i] = nextPossibleMove[i];
            BoardCopy[i] = nextPossibleMove[i];
        }
        k--;
    }
    if (h == 0)
    {
        //printf("\nSuccess!");
        successSteps2 += loop;
        Success2++;
    }
    else
    {
        //printf("\nFailed to find solution!");
        failureSteps2 += loop;
        Failure2++;
    }
    //printf("\n\n sidewaysCount:%i",sidewaysCount);
}

void randomRestart()
{
    if (Success1 > previousSuccess1)
        Success3++;
    else
    {
        int currentSuccess1 = Success1;
        int currentFailure1 = Failure1;
        int currentSucessSteps1 = successSteps1;
        int currentFailureSteps1 = failureSteps1;
        while (Success1 <= previousSuccess1)
        {
            randomRestartCount++;
            for (int i = 0; i < n; i++)
            {
                BoardPos[i] = rand() % n;
                BoardCopy[i] = BoardPos[i];
                initialPos[i] = BoardPos[i];
            }
            hillClimbingSteep();
            numberOfCalls3++;
        } // end while

        randomRestartSteps += (successSteps1 - currentSucessSteps1) + (failureSteps1 - currentFailureSteps1); //(Success1-currentSuccess1)+(Failure1-currentFailure1);
        Success1 = currentSuccess1;
        Failure1 = currentFailure1;
        successSteps1 = currentSucessSteps1;
        failureSteps1 = currentFailureSteps1;
        Success3++;
    } //end else
    //printf("\nRandom restasrt Success!");
}

void randomRestartSideMove()
{
    if (Success2 > previousSuccess2)
        Success4++;
    else
    {
        int currentSuccess2 = Success2;
        int currentFailure2 = Failure2;
        int currentSucessSteps2 = successSteps2;
        int currentFailureSteps2 = failureSteps2;
        while (Success2 <= previousSuccess2)
        {
            randomRestartSideMoveCount++;
            for (int i = 0; i < n; i++)
            {
                BoardPos[i] = rand() % n;
                BoardCopy[i] = BoardPos[i];
                initialPos[i] = BoardPos[i];
            }
            hillClimbingSideMove();
            numberOfCalls4++;
        } // end while

        randomRestartStepsSideMove += (successSteps2 - currentSucessSteps2) + (failureSteps2 - currentFailureSteps2); //(Success2-currentSuccess2)+(Failure2-currentFailure2);
        Success2 = currentSuccess2;
        Failure2 = currentFailure2;
        successSteps2 = currentSucessSteps2;
        failureSteps2 = currentFailureSteps2;
        Success4++;
    } //end else
    //printf("\nRandom restasrt with side Moves Success!");
}

int main()
{
    cout << "Hello World";
    cout << "\n"
         << "Enter n value:"
         << "\n";
    std::cin >> n;
    //cout<<"\n"<<"Enter initial board position:"<<"\n";
    //for(int i=0;i<n;i++)
    //std::cin >>BoardPos[i] ;

    //    Start iteration: 500
    for (int itr = 0; itr < numberOfRuns; itr++)
    {
        for (int i = 0; i < n; i++)
        {
            BoardPos[i] = rand() % n;
            BoardCopy[i] = BoardPos[i];
            initialPos[i] = BoardPos[i];
        }
        previousSuccess1 = Success1;
        previousSuccess2 = Success2;

        printf("\nInitial board position: ");
        printArray();

        //Call steepest-ascent hill climbing
        hillClimbingSteep();

        //printf("\n\n\n");
        initializeBoard();

        //Call Hill-climbing search with sideways move
        hillClimbingSideMove();

        //printf("\n\n\n");
        initializeBoard();

        //Call Random-restart  hill-climbing WITHOUT sideway move
        randomRestart();

        //printf("\n\n\n");
        initializeBoard();

        //Call Random-restart  hill-climbing with sideway move
        randomRestartSideMove();
    } //end For
    printSuccessFailure();
    return 0;
}
