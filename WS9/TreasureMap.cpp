/*----------------------------------------------
// Workshop 9 - Multi-Threading
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas - martinez@myseneca.ca
ID:		112073218
Date:	Nov 27th, 2022
--------------------
// TreasureMap.cpp
// Michael Huang
---------------------------------------------- */

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <future>
#include <functional>

#include "TreasureMap.h"

namespace sdds{

    size_t digForTreasure(const std::string& str, char mark){
        size_t cnt = 0;
        for (auto& x : str){
            if (x == mark){
                cnt++;
            }
        }
        return cnt;
    }

    TreasureMap::TreasureMap(const char* filename){
        std::fstream fin(filename);
        if (fin){
            fin >> rows;
            fin.ignore();
            map = new std::string[rows];
            size_t idx = 0;
            while(fin){
                getline(fin, map[idx]);
                idx++;
            }
            colSize = map[0].length();
        }
        else {
            throw std::string(filename) + " cannot be opened";
        }
    }

    TreasureMap::~TreasureMap(){
        delete [] map;
    }

    std::ostream& TreasureMap::display(std::ostream& os) const{
        if (map){
            for (size_t i = 0; i < rows; ++i){
                os << map[i] << std::endl;
            }
        }
        else 
            os << "The map is empty!" << std::endl;
        return os;
    }

    void TreasureMap::enscribe(const char* filename){
        // Binary write
        if (map){
            // TODO: Open a binary file stream to the filename and
            //         then write the row number to the binary file 
            //         then each of the rows of the map.
            //       If the file cannot be open, raise an exception to
            //         inform the client.

            std::fstream out(filename, std::ios::out | std::ios::binary);
            if (out.is_open()) {
                out.write(reinterpret_cast<char*>(&rows), sizeof(rows)); //Number of rows
                out.write(reinterpret_cast<char*>(&colSize), sizeof(colSize)); //Size of every row
                for (auto i = 0u; i < rows; ++i) {
                    out.write(reinterpret_cast<char*>(&map[i][0]), colSize); //Write the row themselves
                }
                out.close();
            }
            else {
                throw "EXC: File cannot be open";
            }


            // ------------ END TODO ------------
        }
        else{
            throw std::string("Treasure map is empty!");
        }
    }

    void TreasureMap::recall(const char* filename){
        // Binary read
        // TODO: Open a binary file stream to the filename
        //         and read from it to populate the current object.
        //       The first 4 bytes of the file will be the number of rows
        //         for the map followed another 4 bytes for the colSize
        //         of each row in the map.
        //       Afterwards is each row of the map itself.
        //       If the file cannot be open, raise an exception to inform
        //         the client.

        std::fstream in(filename, std::ios::in | std::ios::binary);
        if (in.is_open()) {
            in.read(reinterpret_cast<char*>(&rows), sizeof(rows)); //Read 4 bytes
            in.read(reinterpret_cast<char*>(&colSize), sizeof(colSize)); //Read 4 bytes
            if (map == nullptr) {
                map = new std::string[rows];
            }
            for (auto i = 0u; i < rows; ++i) {      
                map[i].resize(colSize);
                in.read(reinterpret_cast<char*>(&map[i][0]), colSize); 
            }
        }
        else {
            throw "EXC: File cannot be opened";
        }

        in.close();
         // ------------ END TODO ------------
    }

    void TreasureMap::clear(){
        delete [] map;
        map = nullptr;
        rows = 0;
        colSize = 0;
    }

    size_t TreasureMap::findTreasure(char mark)
    {
        size_t count = 0;

        // TODO: For part 2, comment this "for" loop and write the multihreaded version.
        /*for (size_t i = 0; i < rows; ++i){
            count += digForTreasure(map[i], mark);
        }*/

        //Partition Data
        std::string mapPartA = map[0] + map[1] + map[2];
        std::string mapPartB = map[3] + map[4] + map[5];
        std::string mapPartC = map[6] + map[7] + map[8];
        std::string mapPartD = map[9] + map[10] + map[11];
   
        //Binding function digForTreasure to arguments
        auto funcA = std::bind(digForTreasure, mapPartA, mark);
        auto funcB = std::bind(digForTreasure, mapPartB, mark);
        auto funcC = std::bind(digForTreasure, mapPartC, mark);
        auto funcD = std::bind(digForTreasure, mapPartD, mark);

        //auto func = std::bind(digForTreasure, std::placeholders::_1, mark); //I could not make placeholders to work as arguments to the packaged_task

        //Create some packaged_tasks with the bound version of digForTreasure()
        std::packaged_task<size_t()> ptA(funcA);
        std::packaged_task<size_t()> ptB(funcB);
        std::packaged_task<size_t()> ptC(funcC);
        std::packaged_task<size_t()> ptD(funcD);
     

        //Associate packaged_tasks with future objects to eventually retrieve the result of those tasks
        std::future<size_t> fA = ptA.get_future();
        std::future<size_t> fB = ptB.get_future();
        std::future<size_t> fC = ptC.get_future();
        std::future<size_t> fD = ptD.get_future();

        //Create some threads and provide them the packaged_tasks and the partitioned data to be processed
        std::thread thread_A(std::move(ptA));
        std::thread thread_B(std::move(ptB));
        std::thread thread_C(std::move(ptC));
        std::thread thread_D(std::move(ptD));

        //Wait for the child threads to finish
        thread_A.join();
        thread_B.join();
        thread_C.join();
        thread_D.join();

        //Retrieve the data from the futures once the threads have completed their tasks
        count = fA.get() + fB.get() + fC.get() + fD.get();

        return count;
    }

   
}

   