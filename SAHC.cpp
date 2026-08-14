#include <cstddef>
#include <bitset>
#include <cstdlib>
#include <print>

//TODO : Implement the ploting capabilities and benchmark the different GA's + the random one

#include "esoteric.h"

#define PRINT_DETAILS

enum executionMethod
{
    leftToRight,
    rightToLeft,
    startingFromRandom,
};

template <std::size_t numbersOfRuns=100,std::size_t sizeOfBitString=8>
requires (numbersOfRuns >= 1 && sizeOfBitString >= 2)
class SAHC
{

private :

    std::bitset<sizeOfBitString> targetBitString = { } ;
    std::bitset<sizeOfBitString> currentBitString  = { } ;
    std::size_t currentBitStringInverseHammingDistance { } ;
    
    void generateStarterBitString ()
    {
        int bitStringRandomPosition { } ;
        
        for(std::size_t index {0uz} ; index < sizeOfBitString ; index ++)
        {
            bitStringRandomPosition = prng::getInt(0,static_cast<int>(sizeOfBitString-1)) ;

            currentBitString.flip(bitStringRandomPosition);
        }

        #ifdef PRINT_DETAILS
        std::println("Pseudorandomly generated initial bit string : {}",currentBitString.to_string());
        #endif    
    }

public :

    SAHC() = default ;
    ~SAHC() = default ;

    std::size_t targetCurrentInverseHammingDistance()
    {
        currentBitStringInverseHammingDistance = 0 ;
        
        for(std::size_t positionIndex { } ; positionIndex < sizeOfBitString ; positionIndex ++)
        {
            if(currentBitString[positionIndex] == targetBitString[positionIndex])
                currentBitStringInverseHammingDistance += 1 ;
        }

        return currentBitStringInverseHammingDistance ; 
    }

    void mutateCurrentBitStringRightToLeft()
    {
        currentBitStringInverseHammingDistance = targetCurrentInverseHammingDistance() ;

        #ifdef PRINT_DETAILS
        std::println("Inverse hamming distance of current bit string : {} ,against target : {} is Hamming distance : {}",currentBitString.to_string(),targetBitString.to_string(),currentBitStringInverseHammingDistance);
        #endif
        
        if(currentBitStringInverseHammingDistance == sizeOfBitString)
        {
            std::println("Target reached : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::exit(EXIT_SUCCESS);
        }
        else if(currentBitStringInverseHammingDistance == 0)
        {
            #ifdef PRINT_DETAILS
            std::println("Current bit string is the opposite of target, flipping all current bit string bits...");
            #endif
            
            currentBitString.flip();
            
            std::println("Target matched : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::exit(EXIT_SUCCESS);
        }

        static std::size_t positionIndex = 0 ;

        currentBitString.flip(positionIndex) ;

        std::size_t oldHammingDistance = currentBitStringInverseHammingDistance ;

        if(targetCurrentInverseHammingDistance() > oldHammingDistance)
        {
            positionIndex += 1 ;
            return ;
        }
        else
            currentBitString.flip(positionIndex) ;

        if(positionIndex == (sizeOfBitString -1))
            positionIndex = 0 ;

        positionIndex += 1 ;

        return ;
    }

    void mutateCurrentBitStringLeftToRight()
    {
        currentBitStringInverseHammingDistance = targetCurrentInverseHammingDistance() ;

        #ifdef PRINT_DETAILS
        std::println("Inverse hamming distance of current bit string : {} ,against target : {} is Hamming distance : {}",currentBitString.to_string(),targetBitString.to_string(),currentBitStringInverseHammingDistance);
        #endif
        
        if(currentBitStringInverseHammingDistance == sizeOfBitString)
        {
            std::println("Target reached : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::exit(EXIT_SUCCESS);
        }
        else if(currentBitStringInverseHammingDistance == 0)
        {
            #ifdef PRINT_DETAILS
            std::println("Current bit string is the opposite of target, flipping all current bit string bits...");
            #endif
            
            currentBitString.flip();
            
            std::println("Target matched : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::exit(EXIT_SUCCESS);
        }

        static std::size_t positionIndex = sizeOfBitString - 1 ;

        #ifdef PRINT_DETAILS
        std::println("Current position index : {}",positionIndex);
        #endif
        
        currentBitString.flip(positionIndex) ;

        #ifdef PRINT_DETAILS
        std::println("Current bit string state : {}",currentBitString.to_string());
        #endif

        std::size_t oldInverseHammingDistance = currentBitStringInverseHammingDistance ;

        #ifdef PRINT_DETAILS
        std::println("Old inverse hamming distance : {}",oldInverseHammingDistance);
        #endif

        if(targetCurrentInverseHammingDistance() > oldInverseHammingDistance)
        {
            #ifdef PRINT_DETAILS
            std::println("New bit string better");
            #endif

            positionIndex -= 1 ;
            
            return;
        }
        else
        {
            #ifdef PRINT_DETAILS
            std::println("Old bit string better");
            #endif
            currentBitString.flip(positionIndex);
        }
        
        if(positionIndex == 0)
        {
            #ifdef PRINT_DETAILS
            std::println("Position index reset");
            #endif

            positionIndex = sizeOfBitString - 1;

            #ifdef PRINT_DETAILS
            std::println("New position index : {}",positionIndex);
            #endif

            return ;
        }
        
        positionIndex -= 1 ;

        return ;
    }

    void mutateCurrentBitsRandomStartingPosition()
    {
        currentBitStringInverseHammingDistance = targetCurrentInverseHammingDistance() ;

        #ifdef PRINT_DETAILS
        std::println("Inverse hamming distance of current bit string : {} ,against target : {} is Hamming distance : {}",currentBitString.to_string(),targetBitString.to_string(),currentBitStringInverseHammingDistance);
        #endif
        
        if(currentBitStringInverseHammingDistance == sizeOfBitString)
        {
            std::println("Target reached : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::exit(EXIT_SUCCESS);
        }
        else if(currentBitStringInverseHammingDistance == 0)
        {
            #ifdef PRINT_DETAILS
            std::println("Current bit string is the opposite of target, flipping all current bit string bits...");
            #endif
            
            currentBitString.flip();
            
            std::println("Target matched : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::exit(EXIT_SUCCESS);
        }

        static std::size_t positionIndex = prng::getInt(0,static_cast<int>(sizeOfBitString-1)) ;

        currentBitString.flip(positionIndex) ;

        std::size_t oldHammingDistance = currentBitStringInverseHammingDistance ;

        if(targetCurrentInverseHammingDistance() > oldHammingDistance)
        {
            if((positionIndex + 1 > sizeOfBitString -1) && (positionIndex - 1 == 0))
            {
                if(prng::getInt(0,1) >= 0.5)
                    positionIndex += 1 ;
                else
                    positionIndex -= 1 ;
            }
            return ;
        }
        else
            currentBitString.flip(positionIndex) ;

        if(positionIndex == (sizeOfBitString -1) || positionIndex == 0)
            positionIndex = prng::getInt(0,static_cast<int>(sizeOfBitString -1)) ;

        if(prng::getInt(0,1) >= 0.5)
            positionIndex += 1 ;
        else
            positionIndex -= 1 ;

        return ;
    }

    void acquireTargetBitString(std::string bitString)
    {
        targetBitString = static_cast<std::bitset<sizeOfBitString>>(bitString) ;
        
        #ifdef PRINT_DETAILS
        std::println("Acquired target bit string : {}",targetBitString.to_string());
        #endif

        return ;
    }

    void initializeRun(executionMethod method)
    {
        generateStarterBitString() ;
        
        targetCurrentInverseHammingDistance() ;
        
        for(std::size_t executionCounter {0uz} ; executionCounter < numbersOfRuns ; executionCounter ++)
        {
            
            switch(method)
            {
                case executionMethod::leftToRight : mutateCurrentBitStringLeftToRight() ;
                break ;
                case executionMethod::rightToLeft : mutateCurrentBitStringRightToLeft() ;
                break ;
                case executionMethod::startingFromRandom : mutateCurrentBitsRandomStartingPosition() ;
                break ;
                default : mutateCurrentBitStringLeftToRight() ;
            }

            #ifdef PRINT_DETAILS
            std::println("Current bit string : {} ,generation count : {}",currentBitString.to_string(),executionCounter+1);
            #endif
        }
        
        std::println("Hilltop evaluation concluded closest match to be : {}",currentBitString.to_string()) ;
    }

};

int main()
{
    SAHC GA { } ;

    GA.acquireTargetBitString("01010100") ;
    GA.initializeRun(executionMethod::startingFromRandom);

    return 0;
}
