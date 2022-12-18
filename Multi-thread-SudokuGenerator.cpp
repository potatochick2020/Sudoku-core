#include "Multi-thread-SudokuGenerator.h"
#include "Mode.h"


void generateSudokuAndInsertTask_use_ATOMIC(int x,DatabaseConnection DB,atomic<int> &successTask,atomic<int> &failTask){
    for (int i = 0; i<15;i++){ 
        Sudoku sudoku;
        sudoku.initialize(); 
        string to_insert = sudoku.getFlattenBoard();
        cout<<" Thread "<<x<<" : "<<"INSERT INTO Sudoku (SudokuValue) Values ('"+to_insert+"');"<<endl;
        DB.insertData("INSERT INTO Sudoku (SudokuValue) Values ('"+to_insert+"');")==0? successTask.fetch_add(1):failTask.fetch_add(1); // uncomment the deleteData above to avoid duplicates
    }
}
void generateSudokuAndInsertTask_use_MUTEX(int x,DatabaseConnection DB, std::mutex &successTask_mutex, std::mutex &failTask_mutex,int &successTask, int &failTask){
    for (int i = 0; i<15;i++){ 
        Sudoku sudoku;
        sudoku.initialize(); 
        string to_insert = sudoku.getFlattenBoard(); 
        if (DB.insertData("INSERT INTO Sudoku (SudokuValue) Values ('"+to_insert+"');") == 0){
            successTask_mutex.lock();
            successTask++;
            successTask_mutex.unlock();
        } else {
            failTask_mutex.lock();
            failTask++;
            failTask_mutex.unlock();
        }
    }
}
void generateSudokuAndInsertTask_use_INT(int x,DatabaseConnection DB,std::vector<int>&successTask,std::vector<int> &failTask){
    for (int i = 0; i<15;i++){ 
        Sudoku sudoku;
        sudoku.initialize(); 
        string to_insert = sudoku.getFlattenBoard();
        // cout<<" Thread "<<x<<" : ";
        DB.insertData("INSERT INTO Sudoku (SudokuValue) Values ('"+to_insert+"');")==0? successTask[x]++:failTask[x]++; // uncomment the deleteData above to avoid duplicates
    }
}
void multi_thread_sudoku_generator()
{
    //connect to database
    std::cout<<"Multi Thread Generator"<<std::endl;
    const char* dir = R"(../Database/SudokuDatabase.db)";
    auto DB = DatabaseConnection(dir);
    DB.createTableIfNotExist(); 
    //Start time counting 
    auto t1 = std::chrono::high_resolution_clock::now();

    std::cout << "\x1b[32m Start helpers... \x1b[0m" << std::endl; 

    //create vector to hold thread
    vector<std::thread> threadList; 
    


    //create thread and push to vector
    //generate and insert 25 sudoku each thread, 25 * 4 = 100 sudoku in total
    #if defined(_use_ATOMIC)
        std::cout<<"using ATOMIC"<<std::endl;
        //create atomic int fail and success task to hold total number of fail and success task
        std::atomic_int successTask = {0};
        std::atomic_int failTask = {0};
        for (int i = 0;i<NUMBER_OF_THREADS;i++){
            threadList.push_back(std::thread(generateSudokuAndInsertTask_use_ATOMIC,i,DB, std::ref(successTask), std::ref(failTask)));
        }  
    #elif defined(_use_MUTEX)
        std::cout<<"Using MUTEX"<<std::endl;
        int successTask=0;
        int failTask=0;
        std::mutex successTask_mutex;
        std::mutex failTask_mutex;
        for (int i = 0;i<NUMBER_OF_THREADS;i++){
            threadList.push_back(std::thread(generateSudokuAndInsertTask_use_MUTEX,i,DB, std::ref(successTask_mutex), std::ref(failTask_mutex), std::ref(successTask), std::ref(failTask)));
        }
    #elif defined(_use_INT)
        std::cout<<"Using INT"<<std::endl;
        std::vector<int> successTaskVector(NUMBER_OF_THREADS,0);
        std::vector<int> failTaskVector(NUMBER_OF_THREADS,0);
        for (int i = 0;i<NUMBER_OF_THREADS;i++){
            threadList.push_back(std::thread(generateSudokuAndInsertTask_use_INT,i,DB, std::ref(successTaskVector), std::ref(failTaskVector)));
        } 
        int successTask=0;
        int failTask=0;
        for (auto x: successTaskVector) successTask += x;
        for (auto x: failTaskVector) failTask += x;
    #endif 
     

    for (auto& th : threadList) {
        th.join();
    } 

    std::cout << "\x1b[32m All helpers to finish... \x1b[0m" << std::endl; 

    //End time counting 
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;

    //print used time
    std::cout << "\x1b[32m Used Time:" << ms_double.count() << "ms to complete "<<successTask<<" Success insertion and "<<failTask<<" Fail insertion \x1b[0m \n";

    //disconnect database
    DB.closeConnection(); 
}

