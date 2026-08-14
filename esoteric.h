#pragma once 

#include <random>

namespace prng
{

    inline std::mt19937_64 generate() 
    {
        thread_local std::random_device rd ; //thread_local so each thread get a different seed

        thread_local std::seed_seq seed_collection { rd() , rd() , rd() , rd() , rd() , rd() , rd() } ;

        return std::mt19937_64 ( seed_collection ) ;
    }

    inline thread_local std::mt19937_64  mt { generate() } ; //Can be called from any file ( stand-alone instance ) , thread local for the same reason
    //otherwise all threads use the same random value at each respective simualation , mt19937_64 to avoid repetitiond in random number generations

    template < typename T > 
    T getInt(T min , T max)
    {
        return std::uniform_int_distribution<T>{ min , max }(mt) ;
    }


}


/*
#include <cstddef>
#include <bitset>
#include <cstdlib>
#include <print>

#include "esoteric.h"

#define PRINT_DETAILS

enum class executionMethod
{
    leftToRight,
    RightToLeft,  
};

template <std::size_t numbersOfRuns=100,std::size_t sizeOfBitString=8>
requires (numbersOfRuns >= 1 && sizeOfBitString >= 4)
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

            currentBitString[bitStringRandomPosition].flip();
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
            
            for(std::size_t positionIndex {0uz} ; positionIndex < sizeOfBitString ; positionIndex ++)
            {
                currentBitString[positionIndex].flip();
            }
            
            std::println("Target matched : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::exit(EXIT_SUCCESS);
        }

        static std::size_t positionIndex = 0 ;

        currentBitString[positionIndex].flip() ;

        std::size_t oldHammingDistance = currentBitStringInverseHammingDistance ;

        if(targetCurrentInverseHammingDistance() > oldHammingDistance)
            return;
        else
            currentBitString[positionIndex].flip();

        if(positionIndex == (sizeOfBitString -1))
            positionIndex = 0 ;

        positionIndex += 1 ;

        return ;
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
            
            for(std::size_t positionIndex {0uz} ; positionIndex < sizeOfBitString ; positionIndex ++)
            {
                currentBitString[positionIndex].flip();
            }
            
            std::println("Target matched : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::exit(EXIT_SUCCESS);
        }

        static std::size_t positionIndex = sizeOfBitString - 1 ;

        #ifdef PRINT_DETAILS
        std::println("Current position index : {}",positionIndex);
        #endif
        
        currentBitString[positionIndex].flip() ;

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
            return;
        }
        else
        {
            #ifdef PRINT_DETAILS
            std::println("Old bit string better");
            #endif
            currentBitString[positionIndex].flip();
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
            if(method == executionMethod::leftToRight)
                mutateCurrentBitStringLeftToRight() ;
            else if(method == executionMethod::RightToLeft)
                mutateCurrentBitStringRightToLeft() ;

            #ifdef PRINT_DETAILS
            std::println("Current bit string : {} ,generation count : {}",currentBitString.to_string(),executionCounter+1);
            #endif
        }
        
        std::println("Hilltop evaluation concluded closest match to be : {}",currentBitString.to_string()) ;
    }

};

int main()
{
    [[maybe_unused]] SAHC<10,4> GA { } ;

    GA.acquireTargetBitString("1010") ;
    GA.initializeRun(executionMethod::RightToLeft) ;

    return 0;
}

*/
