#include <iostream>

using namespace std;

// The following function returns the nearest neighbours of an element x in a Karnaugh Map of n variables
int* nearestNeigh(int x, int n)
{
    // Pointer to list of nearest neighbours
    int* list = (int*)malloc(n * sizeof(int));

    // Variable for XORing
    int control = 1;

    // Generate
    int temp;
    for(int i = 0; i < n; i++)
    {
        // Generate neighbour
        temp = x ^ control;

        // Store
        list[i] = temp;

        // Update control
        control = control << 1;
    }

    // Return answer
    return list;
}
// WARNING: Free memory after using this function!!!!

// The following function prints the list of nearest neighbours of an element x in a Karnaugh Map of n variables
void printNearestNeigh(int x, int n)
{
    // Get nearest neighbours
    int* list = nearestNeigh(x, n);

    // Print list
    int j;
    for(j = 0; j < n-1; j++)
    {
        cout << list[j] << ":";
    }
    cout << list[j] << endl;

    // Free memory + return
    free(list); 
    return;
}

// -----------------------------------------ONLY FOR REFERENCE------------------------------------------------
//____________________________________________________________________________________________________________
// The following function prints all sets of 2 for a given element in an n-variable Karnaugh map
void gen2(int x, int n)
{
    // Get nearest neighbours
    int* list = nearestNeigh(x, n);

    // Print list of 2's
    int i;
    for(i = 0; i < n; i++)
    {
        cout << "[" << x << ":" << list[i] << "]" << endl;
    }

    // Free memory + return
    free(list);
    return;
}

// The following function prints all sets of 4 for a given element in an n-variable Karnaugh map
void gen4(int x, int n)
{
    // Get nearest neighbours
    int* list = nearestNeigh(x, n);

    // Print list of 4's
    int i, j;
    int temp;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < i; j++)
        {
            temp = x ^ list[i] ^ list[j];
            cout << "[" << x << ":" << list[i] << ":" << temp << ":" << list[j] << "]" << endl;
        }
    }

    // Free memory + return
    free(list);
    return;
}

// The following function prints all sets of 8 for a given element in an n-variable Karnaugh Map
void gen8(int x, int n)
{
    // Get nearest neighbours
    int* list = nearestNeigh(x, n);

    // Print list of 8's
    int i, j, k;
    int temp1, temp2, temp3, temp4;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < i; j++)
        {
            for(k = 0; k < j; k++)
            {
                temp1 = x ^ list[i] ^ list[j];
                temp2 = x ^ list[j] ^ list[k];
                temp3 = x ^ list[k] ^ list[i];
                temp4 = list[i] ^ list[j] ^ list[k];
                cout << "[" << x << ":" << list[i] << ":" << temp1 << ":" << list[j] << ":" << temp2 << ":" << list[k] << ":" << temp3 << ":" << temp4 << "]" << endl;
            }
        }
    }

    // Free memory + return
    free(list);
    return;
}
//________________________________________________________________________________________________________________

// The following function prints a four variable Karnaugh Map
void printK4(bool map[16])
{
    cout << " _______ _______ _______ _______ " << endl;
    cout << "|" << map[0] << "\t|" << map[4] << "\t|" << map[12] << "\t|" << map[8] << "\t|" << endl;
    cout << "|_______|_______|_______|_______|" << endl;
    cout << "|" << map[1] << "\t|" << map[5] << "\t|" << map[13] << "\t|" << map[9] << "\t|" << endl;
    cout << "|_______|_______|_______|_______|" << endl;
    cout << "|" << map[3] << "\t|" << map[7] << "\t|" << map[15] << "\t|" << map[11] << "\t|" << endl;
    cout << "|_______|_______|_______|_______|" << endl;
    cout << "|" << map[2] << "\t|" << map[6] << "\t|" << map[14] << "\t|" << map[10] << "\t|" << endl;
    cout << "|_______|_______|_______|_______|" << endl;
}

// The following function prints out terms that are combined in a 4 variable Karnaugh map
// Inputs :: Array of minterms (in decimal), size of array 
void essential(int minterms[], int size)
{
    // Special Case
    if(size == 16)
    {
        cout << "-----1-----" << endl;
        return;
    }
    // _________________________________________________________________________________________________
    // -------------------------------------- ESSENTIAL ------------------------------------------------
    // The following function finds all essential implicants of a four - variable Karnaugh map (minterms)
    
    // Number encircled
    int circled = 0;

    // Encircled list (checks if elements are encircled) + Map values
    bool map[16] = {false};
    bool chk[16] = {false};
    bool chkRecent[16] = {false};

    for(int p = 0; p < size; p++)
    {
        map[minterms[p]] = true;
    }

    // Print
    printK4(map);

    // Singleton Elements
    int a, x;
    bool foundMatch = false;
    for(a = 0; a < size; a++)
    {
        int *tempList = nearestNeigh(minterms[a], 4);
        for(x = 0; x < 4; x++)
        {
            if(map[tempList[x]] == true)
            {
                foundMatch = true;
                break;
            }
        }

        // Encircle if no match
        if(!foundMatch)
        {
            cout << minterms[a] << endl;
            chk[minterms[a]] = true;
            circled++;
        }

        // Reset
        foundMatch = false;
        free(tempList);
    }

    // Groups of 2
    bool foundAgain = false;
    int val;
    for(a = 0; a < size; a++)
    {   
        // Ignore if already encircled
        if(chk[minterms[a]]) continue;

        // Attempt to find singular match
        int *tempList = nearestNeigh(minterms[a], 4);
        for(x = 0; x < 4; x++)
        {
            if(map[tempList[x]] && !chk[tempList[x]])
            {
                if(!foundMatch)
                {
                    foundMatch = true;
                    val = tempList[x];
                }
                else
                {
                    foundAgain = true;
                    break;
                }
            }
        }

        // Encircle only if single match
        if(foundMatch && !foundAgain)
        {
            cout << minterms[a] << ":" << val << endl;
            chkRecent[minterms[a]] = true;
            chkRecent[val] = true;
            circled += 2;
        }

        // Reset
        foundMatch = false;
        foundAgain = false;
        free(tempList);
    }

    // Modify chk
    for(int w = 0; w < 16; w++)
    {
        chk[w] = chk[w] || chkRecent[w];
        chkRecent[w] = false;
    }
    

    // Groups of 4
    int y;
    int val1, val2, val3;
    int temp1, temp2, temp3;
    bool mapVal, chkVal;
    for(a = 0; a < size; a++)
    {   
        // Ignore if already encircled
        if(chk[minterms[a]]) continue;

        // Attempt to find singular match
        int *tempList = nearestNeigh(minterms[a], 4);
        for(x = 0; x < 4; x++)
        {
            for(y = 0; y < x; y++)
            {
                // Possible 4 - tuple (val0 = minterms[a])
                temp1 = tempList[x];
                temp2 = minterms[a] ^ tempList[y] ^ tempList[x];
                temp3 = tempList[y];

                // Check if all values are uncircled minterms
                mapVal = map[temp1] && map[temp2] && map[temp3];
                chkVal = chk[temp1] || chk[temp2] || chk[temp3];

                if(mapVal && !chkVal)
                {
                    if(!foundMatch)
                    {
                        foundMatch = true;
                        val1 = temp1;
                        val2 = temp2;
                        val3 = temp3;
                    }
                    else
                    {
                        foundAgain = true;
                        break;
                    }
                }
            }

            if(foundAgain) break;
        }

        // Encircle only if single match
        if(foundMatch && !foundAgain)
        {
            cout << minterms[a] << ":" << val1 << ":" << val2 << ":" << val3 << endl;
            chkRecent[minterms[a]] = true;
            chkRecent[val1] = true;
            chkRecent[val2] = true;
            chkRecent[val3] = true;
            circled += 4;
        }

        // Reset
        foundMatch = false;
        foundAgain = false;
        free(tempList);
    }

    // Modify chk
    for(int w = 0; w < 16; w++)
    {
        chk[w] = chk[w] || chkRecent[w];
        chkRecent[w] = false;
    }

    // Groups of 8
    int z;
    int val4, val5, val6, val7;
    int temp4, temp5, temp6, temp7;
    for(a = 0; a < size; a++)
    {   
        // Ignore if already encircled
        if(chk[minterms[a]]) continue;

        // Attempt to find singular match
        int *tempList = nearestNeigh(minterms[a], 4);
        for(x = 0; x < 4; x++)
        {
            for(y = 0; y < x; y++)
            {
                for(z = 0; z < y; z++)
                {
                    // Possible 8 - tuple (val0 = minterms[a])
                    temp1 = tempList[x];
                    temp2 = tempList[y];
                    temp3 = tempList[z];
                    temp4 = minterms[a] ^ tempList[x] ^ tempList[z];
                    temp5 = minterms[a] ^ tempList[y] ^ tempList[z];
                    temp6 = minterms[a] ^ tempList[x] ^ tempList[y];
                    temp7 = tempList[x] ^ tempList[y] ^ tempList[z];

                    // Check if all values are uncircled minterms
                    mapVal = map[temp1] && map[temp2] && map[temp3] && map[temp4] && map[temp5] && map[temp6] && map[temp7];
                    chkVal = chk[temp1] || chk[temp2] || chk[temp3] || chk[temp4] || chk[temp5] || chk[temp6] || chk[temp7];

                    if(mapVal && !chkVal)
                    {
                        if(!foundMatch)
                        {
                            foundMatch = true;
                            val1 = temp1;
                            val2 = temp2;
                            val3 = temp3;
                            val4 = temp4;
                            val5 = temp5;
                            val6 = temp6;
                            val7 = temp7;
                        }
                        else
                        {
                            foundAgain = true;
                            break;
                        }
                    }
                }
                if(foundAgain) break;
            }
            if(foundAgain) break;
        }

        // Encircle only if single match
        if(foundMatch && !foundAgain)
        {
            cout << minterms[a] << ":" << val1 << ":" << val2 << ":" << val3 << ":" << val4 << ":" << val5 << ":" << val6 << ":" << val7 << endl;
            chkRecent[minterms[a]] = true;
            chkRecent[val1] = true;
            chkRecent[val2] = true;
            chkRecent[val3] = true;
            chkRecent[val4] = true;
            chkRecent[val5] = true;
            chkRecent[val6] = true;
            chkRecent[val7] = true;
            circled += 8;
        }

        // Reset
        foundMatch = false;
        foundAgain = false;
        free(tempList);
    }

    // Modify chk
    for(int w = 0; w < 16; w++)
    {
        chk[w] = chk[w] || chkRecent[w];
        chkRecent[w] = false;
    }

    // _________________________________________________________________________________________________

    // -------------------------------------- COMBINING REMAINING TERMS---------------------------------
    // cout << "Remaining terms:" << endl;
    // for(int q = 0; q < size; q++)
    // {
    //     if(!chk[minterms[q]]) cout << minterms[q] << endl;
    // }
    // cout << endl;
    cout << "-----------------------------------------------------------------------------"<< endl;

    // Control Variables
    int b; 
    int unCircled, tempCircled;

    // Check for groups of eight
    unCircled = 0;
    tempCircled = 1;
    int buffer8[8] = {-1};
    for(b = 0; b < size; b++)
    {
        int *tempList = nearestNeigh(minterms[b], 4);
        if(chk[minterms[b]]) continue;
        for(x = 0; x < 4; x++)
        {
            for(y = 0; y < x; y++)
            {
                for(z = 0; z < y; z++)
                {
                    // Possible 8 - tuple (val0 = minterms[a])
                    val1 = tempList[x];
                    val2 = tempList[y];
                    val3 = tempList[z];
                    val4 = minterms[b] ^ tempList[x] ^ tempList[z];
                    val5 = minterms[b] ^ tempList[y] ^ tempList[z];
                    val6 = minterms[b] ^ tempList[x] ^ tempList[y];
                    val7 = tempList[x] ^ tempList[y] ^ tempList[z];

                    // Check if all values are minterms
                    mapVal = map[val1] && map[val2] && map[val3] && map[val4] && map[val5] && map[val6] && map[val7];

                    if(mapVal)
                    {
                        // Find #uncircled variables
                        chk[val1] ? tempCircled += 0 : tempCircled += 1;
                        chk[val2] ? tempCircled += 0 : tempCircled += 1;
                        chk[val3] ? tempCircled += 0 : tempCircled += 1;
                        chk[val4] ? tempCircled += 0 : tempCircled += 1;
                        chk[val5] ? tempCircled += 0 : tempCircled += 1;
                        chk[val6] ? tempCircled += 0 : tempCircled += 1;
                        chk[val7] ? tempCircled += 0 : tempCircled += 1;
                        
                        // Store in Buffer
                        if (tempCircled > unCircled)
                        {
                            buffer8[0] = minterms[b];
                            buffer8[1] = val1; buffer8[2] = val2; buffer8[3] = val3; buffer8[4] = val4; buffer8[5] = val5; buffer8[6] = val6; buffer8[7] = val7;
                            chk[minterms[b]] = true;
                            chk[val1] = true;
                            chk[val2] = true;
                            chk[val3] = true;
                            chk[val4] = true;
                            chk[val5] = true;
                            chk[val6] = true;
                            chk[val7] = true;

                            // Update uncircled
                            unCircled = tempCircled;
                        }
                        
                        // Reset
                        tempCircled = 1;
                    }
                }
            }
        }
        if(buffer8[0] != -1) 
        {
            cout << buffer8[0] << ":" << buffer8[1] << ":" << buffer8[2] << ":" << buffer8[3] << ":";
            cout << buffer8[4] << ":" << buffer8[5] << ":" << buffer8[6] << ":" << buffer8[7] << endl;
        }
        free(tempList);

        // Reset buffer val
        buffer8[0] = -1;
    }

    // Check for groups of 4
    unCircled = 0;
    tempCircled = 1;
    int buffer4[4] = {-1};
    for(b = 0; b < size; b++)
    {
        if(chk[minterms[b]]) continue;
        int *tempList = nearestNeigh(minterms[b], 4);
        for(x = 0; x < 4; x++)
        {
            for(y = 0; y < x; y++)
            {
                // Possible 4 - tuple (val0 = minterms[a])
                val1 = tempList[x];
                val2 = minterms[b] ^ tempList[y] ^ tempList[x];
                val3 = tempList[y];

                // Check if all values are minterms
                mapVal = map[val1] && map[val2] && map[val3];

                if(mapVal)
                {
                    // Find #uncircled variables
                    chk[val1] ? tempCircled += 0 : tempCircled += 1;
                    chk[val2] ? tempCircled += 0 : tempCircled += 1;
                    chk[val3] ? tempCircled += 0 : tempCircled += 1;

                    // Store in Buffer
                    if (tempCircled > unCircled)
                    {
                        buffer4[0] = minterms[b];
                        buffer4[1] = val1; buffer4[2] = val2; buffer4[3] = val3;
                        chk[minterms[b]] = true;
                        chk[val1] = true;
                        chk[val2] = true;
                        chk[val3] = true;

                        // Update uncircled
                        unCircled = tempCircled;
                    }
                    
                    // Reset
                    tempCircled = 1;
                }
            }
        }
        if(buffer4[0] != -1) cout << buffer4[0] << ":" << buffer4[1] << ":" << buffer4[2] << ":" << buffer4[3] <<endl;
        free(tempList);

        // Reset buffer val
        buffer4[0] = -1;
    }

    // Check for groups of 2
    unCircled = 0;
    int buffer2[2] = {-1};
    for(b = 0; b < size; b++)
    {
        if(chk[minterms[b]]) continue;
        int *tempList = nearestNeigh(minterms[b], 4);
        for(x = 0; x < 4; x++)
        {
            val = tempList[x];
            if(map[val])
            {
                // Find #uncircled variables
                chk[val] ? tempCircled = 1 : tempCircled = 2;

                // Store in buffer
                if(tempCircled > unCircled) 
                {
                    buffer2[0] = minterms[b]; buffer2[1] = val;
                    chk[minterms[b]] = true;
                    chk[val] = true;

                    // Update uncircled
                    unCircled = tempCircled;
                }
            }
        }
        if(buffer2[0] != -1) cout << buffer2[0] << ":" << buffer2[1] << endl;
        free(tempList);

        // Reset buffer value
        buffer2[0] = -1;
    }
    return;
}

int main()
{
    int sample[] = {0, 1, 3, 5, 7, 9, 13, 15};
    essential(sample, 8);

    return(0);
}