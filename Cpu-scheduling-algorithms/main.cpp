# include <iostream> // cout, endl
# include <string.h> // string
# include <vector> // vector
# include <cstdlib> // atoi, system
# include <iomanip> // setw, setprecision
# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <sstream>
# include <math.h>
# include <queue>
# include <cmath>
# include <fstream>

using namespace std ;

class ProcessType {
public:
  int mProcessID = 0 ;
  int mCpuBurst = 0 ;
  int mArrivalTime = 0 ;
  int mPriority = 0 ;

  int mFCFSWTime = 0 ;  
  int mFCFSTurnTime = 0 ;
  int mNSJFWTime = 0 ;
  int mNSJFTurnTime = 0 ;
  int mPSJFWTime = 0 ;
  int mPSJFTurnTime = 0 ;
  int mRRWTime = 0 ;
  int mRRTurnTime = 0 ;
  int mPPWTime = 0 ;
  int mPPTurnTime = 0 ; 
  bool inQueue = false ;
  bool beUsed = false ; 
  int beUsedtime = 0 ; // 紀錄被使用的時間 
};

fstream file ; // 讀檔
static int uTimeslice = 0 ; // 時間片段 
static vector <ProcessType> uAllProcess ; // 存了所有Process狀態
// ------甘特圖------ 
static string uFCFSGrantt = "" ;
static string uNSJFGrantt = "" ; 
static string uPSJFGrantt = "" ; 
static string uRRGrantt = "" ; 
static string uPPGrantt = "" ; 
// ------甘特圖------

void StoreProcess() {
// 將process資料存到uAllProcess中
// type 1 : FCFS 
// type 2 : NSJF
// type 3 : PSJF
// type 4 : RR
// type 5 : PP
// type 6 : All
  string line = "" ;
  getline( file, line ) ; // 將標頭讀去 
  while( getline( file, line ) ) {
	// 第三行開始每行依序為
	// [ProcessID] [CPUBurst] [arrival time] [Priority]
    ProcessType store ;
    int word = 0 ;
    istringstream ss( line ) ;
    ss >> word ;
    store.mProcessID = word ;
    ss >> word ;
    store.mCpuBurst = word ;
    ss >> word ;
    store.mArrivalTime = word ;
    ss >> word ;
    store.mPriority = word ;
    uAllProcess.push_back( store ) ;
  } // while

  file.close() ;
  // 依照ProcessID由小到大排序
  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    for( int j = i ; j < uAllProcess.size() ; j++ ) {
       if ( uAllProcess.at( i ).mProcessID > uAllProcess.at( j ).mProcessID ) {
       // 要是後面的數比較小
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	   } // if 
    } // for
  } // for

} // StoreProcess()

void WriteFile( int type, string filename ) {
// 寫檔
  // 依照ProcessID由小到大排序
  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    for( int j = i ; j < uAllProcess.size() ; j++ ) {
       if ( uAllProcess.at( i ).mProcessID > uAllProcess.at( j ).mProcessID ) {
       // 要是後面的數比較小
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	   } // if 
    } // for
  } // for

  fstream file ;
  filename.erase( filename.begin(), filename.begin() + 5 ) ; // 將"input"給刪除留下數字 
  filename = "output" + filename ;
  file.open( filename.c_str(), ios::out ) ;
  switch( type ) {
    case 1 : // FCFS
      file << "==    FCFS==" << endl ;
	  file << "-" << uFCFSGrantt << endl ;
	  file << "===========================================================" << endl ;
	  file << endl << "Waiting Time" << endl ;
	  file << "ID      FCFS" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID 
		     << std::left << setw(8) << uAllProcess.at( i ).mFCFSWTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
	  file << endl << "Turnaround Time" << endl ;
	  file << "ID      FCFS" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mFCFSTurnTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
    break ;
    case 2 : // NSJF
      file << "==    NSJF==" << endl ;
	  file << "-" << uNSJFGrantt << endl ;
	  file << "===========================================================" << endl ;
	  file << endl << "Waiting Time" << endl ;
	  file << "ID      NSJF" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mNSJFWTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
	  file << endl << "Turnaround Time" << endl ;
	  file << "ID      NSJF" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mNSJFTurnTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
    break ;
    case 3 : // PSJF
      file << "==    PSJF==" << endl ;
	  file << "-" << uPSJFGrantt << endl ;
	  file << "===========================================================" << endl ;
	  file << endl << "Waiting Time" << endl ;
	  file << "ID      PSJF" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mPSJFWTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
	  file << endl << "Turnaround Time" << endl ;
	  file << "ID      PSJF" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) <<uAllProcess.at( i ).mPSJFTurnTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
    break ;
    case 4 : // RR
      file << "==      RR==" << endl ;
	  file << "-" << uRRGrantt << endl ;
	  file << "===========================================================" << endl ;
	  file << endl << "Waiting Time" << endl ;
	  file << "ID        RR" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mRRWTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
	  file << endl << "Turnaround Time" << endl ;
	  file << "ID        RR" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mRRTurnTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
    break ;
    case 5 : // PP
      file << "==      PP==" << endl ;
	  file << "-" << uPPGrantt << endl ;
	  file << "===========================================================" << endl ;
	  file << endl << "Waiting Time" << endl ;
	  file << "ID  Priority" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mPPWTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
	  file << endl << "Turnaround Time" << endl ;
	  file << "ID  Priority" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mPPTurnTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
    break ;
    case 6 : // 全部
      file << "==    FCFS==" << endl ;
	  file << "-" << uFCFSGrantt << endl ;
      file << "==      RR==" << endl ;
	  file << "-" << uRRGrantt << endl ;
      file << "==    PSJF==" << endl ;
	  file << "-" << uPSJFGrantt << endl ;
      file << "==Non-PSJF==" << endl ;
	  file << "-" << uNSJFGrantt << endl ;
      file << "== Priority==" << endl ;
	  file << "-" << uPPGrantt << endl ;
	  file << "===========================================================" << endl 
	       << "                                                                                " ;
	  file << endl << "Waiting Time" << endl ;
	  file << "ID      FCFS    RR      PSJF    NPSJF   Priority" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mFCFSWTime 
		     << std::left << setw(8) << uAllProcess.at( i ).mRRWTime << std::left << setw(8) << uAllProcess.at( i ).mPSJFWTime 
			 << std::left << setw(8) << uAllProcess.at( i ).mNSJFWTime << uAllProcess.at( i ).mPPWTime<< endl ;
	  } // for
	  file << "===========================================================" << endl ;
	  file << endl << "Turnaround Time" << endl ;
	  file << "ID      FCFS    RR      PSJF    NPSJF   Priority" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mFCFSTurnTime 
		     << std::left << setw(8) << uAllProcess.at( i ).mRRTurnTime << std::left << setw(8) << uAllProcess.at( i ).mPSJFTurnTime 
			 << std::left << setw(8) << uAllProcess.at( i ).mNSJFTurnTime << uAllProcess.at( i ).mPPTurnTime  << endl ;
	  } // for
	  file << "===========================================================" << endl ;
    break ;
    default:
    break ;	
  } // switch 

  file.close() ;
} // WriteFile()

void FCFSMethod() {
// First Come First Served
// Non-preemptive
// 後到先執行///機測改良版 
   int CycleSum = 0 ; // 總共需要花多少時間
  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    // 依照ArrivalTime由小到大排序
    for( int j = i + 1 ; j < uAllProcess.size() ; j++ ) {
      if ( uAllProcess.at( i ).mArrivalTime < uAllProcess.at( j ).mArrivalTime ) {
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // if
      else if ( uAllProcess.at( i ).mArrivalTime == uAllProcess.at( j ).mArrivalTime ) {
       // 同時抵達、Priority小的放前面 
        if ( uAllProcess.at( i ).mPriority > uAllProcess.at( j ).mPriority )
          swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // else if
    } // for
  } // for

  for ( int i = 0 ; i < uAllProcess.size() ; i++ ) CycleSum = CycleSum + uAllProcess.at( i ).mCpuBurst ; 
  int count = 1 ; // Cycle、用來計算Turnaround、Waiting Time
  ProcessType RunProcess ;
  int NextArrivalProcess = 0 ; // 紀錄下一個需要放進去Queue的Process位址 
  vector< ProcessType > Process = uAllProcess ; 
  vector< ProcessType > ReadQueue ; // 準備佇列 
  while ( count <= CycleSum ) {
    // 將已經抵達的Process放入Queue中，不包含已經完成的Process 
    for( int i = 0 ; i < Process.size() ; i++ ) {
      if( Process.at( i ).mArrivalTime <= count && Process.at( i ).mCpuBurst != 0 && !Process.at( i ).inQueue ) {
        ReadQueue.push_back( Process.at( i ) ) ;
        Process.at( i ).inQueue = true ;
	  } // if
	} // for
    // for ( int i = 0 ; i < ReadQueue.size() ; i++ ) cout << ReadQueue.at(i).mProcessID << "-" <<ReadQueue.at(i).beUsedtime << " ";
	// cout << endl << "------------------------"  << endl ; 
    // 將Queue排序
    if ( ReadQueue.size() > 0 ) {
      for ( int i = 0 ; i < ReadQueue.size() ; i++ ) {
        for ( int j = i + 1 ; j < ReadQueue.size() ; j++ ) { 
	      if ( ReadQueue.at( j ).mArrivalTime > ReadQueue.at( i ).mArrivalTime ) {
	          // Priority相同，且兩個都用過或都沒用過，則早到的先執行 
            swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
		  } // else if
          else if ( ReadQueue.at( j ).mArrivalTime == ReadQueue.at( i ).mArrivalTime 
                    && ReadQueue.at( j ).mProcessID > ReadQueue.at( i ).mProcessID ) {
            // Priority相同，且兩個都用過或都沒用過、ArrivalTime相同，ProcessId小的排前面 
		    swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
          } // else if
 	    } // for
	  } // for
       //for ( int i = 0 ; i < ReadQueue.size() ; i++ ) cout << ReadQueue.at(i).mProcessID << "-" <<ReadQueue.at(i).beUsedtime << " ";
	   //cout << endl << endl << endl << endl ; 
      // 設定正在執行的Process、設定甘特圖
      //cout << RunProcess.mProcessID << endl ;
      for( int i = 0 ; i < Process.size() ; i++ ) {
        if( Process.at( i ).mProcessID == ReadQueue.front().mProcessID ) {
          Process.at( i ).mCpuBurst = Process.at( i ).mCpuBurst - 1 ; // 執行一個Cycle需要的time-1
          if ( !ReadQueue.front().beUsed ) ReadQueue.front().beUsedtime = count ; // 紀錄CPU使用過的時間
          ReadQueue.front().beUsed = true ; 
          ReadQueue.front().mCpuBurst = ReadQueue.front().mCpuBurst - 1 ;
          char id = '\0' ;
          if ( Process.at( i ).mProcessID > 9 ) { // 10以上的數用英文字表示
            id = Process.at( i ).mProcessID + '7' ;
	      } // if
          else {
            id = Process.at( i ).mProcessID + '0' ;
	      } // else 
          uFCFSGrantt = uFCFSGrantt + id ; // 放入甘特圖  
	    } // if
	  } // for

      // 計算Waiting time  
      // ReadQueue裡除了第一個Process以外，都在Waiting、如果Arrival也就會在ReadyQueue中 
      for ( int i = 1  ; i < ReadQueue.size() ; i++ ) {
        for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
          if ( uAllProcess.at( j ).mProcessID == ReadQueue.at( i ).mProcessID ) {
            // 不放到Process直接放到uAllProcess 
            uAllProcess.at( j ).mFCFSWTime = uAllProcess.at( j ).mFCFSWTime + 1 ;
          } // if 
        } // for 
      } // for
      // 結束的Process從Queue移除
  	  RunProcess = ReadQueue.front()  ;
      if ( RunProcess.mCpuBurst == 0 ) {
        ReadQueue.erase( ReadQueue.begin() ) ;
  	  } // if
	} // if
	else {
	  // 若CPU為閒置，一樣紀錄 
      uFCFSGrantt = uFCFSGrantt + "-" ;	
      CycleSum++ ;
	} // else 

    count++ ;
  } // while 

  // 計算Turnaround time  
  // Turnaroundtime = waiting time + burst time
  for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
    uAllProcess.at( j ).mPPTurnTime = uAllProcess.at( j ).mPPWTime + uAllProcess.at( j ).mCpuBurst ;
  } // for 

  // cout << uFCFSGrantt << endl ;
  // for ( int i = 0 ; i < uAllProcess.size() ; i++ ) cout << uAllProcess.at( i ).mFCFSWTime << endl ;; 
} // FCFS()

void NSJFMethod() {
// Shortest Job First
// Non-preemptive
// 每次執行Process前，將在Ready Queue的Process依據burst由小到大
// burst相同則依據ArrivalTime由小到大 

  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    // 依照ArrivalTime由小到大排序
    for( int j = i ; j < uAllProcess.size() ; j++ ) {
      if ( uAllProcess.at( i ).mArrivalTime > uAllProcess.at( j ).mArrivalTime ) {
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // if
      else if ( uAllProcess.at( i ).mArrivalTime == uAllProcess.at( j ).mArrivalTime ) {
       // 同時抵達、burst小的放前面 
        if ( uAllProcess.at( i ).mCpuBurst > uAllProcess.at( j ).mCpuBurst )
          swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // else if  
    } // for
  } // for

  int count = 1 ; // Cycle、用來計算Turnaround、Waiting Time 
  for ( int i = 0 ; i < uAllProcess.size() ; i++ ) {
  // 由BurstTime最小的開始跑、放入甘特圖
    if ( count >= uAllProcess.at( i ).mArrivalTime ) {
      // uAllProcess到達
      for ( int k = i ; k < uAllProcess.size() ; k++ ) {
        // 需要判斷已到達的有那些，去做排序
        for ( int j = k ; j < uAllProcess.size() ; j++ ) {
          if ( count >= uAllProcess.at( j ).mArrivalTime && uAllProcess.at( j ).mCpuBurst < uAllProcess.at( k ).mCpuBurst ) {
            // 已到達的uAllProcess，如果Cpuburst較小則先執行 
            swap( uAllProcess.at( j ), uAllProcess.at( k ) ) ; 
	      } // if
	      else if ( count >= uAllProcess.at( j ).mArrivalTime && uAllProcess.at( j ).mCpuBurst == uAllProcess.at( k ).mCpuBurst ) {
	        // Cpuburst相同，則早到的先執行 
            if ( uAllProcess.at( j ).mArrivalTime < uAllProcess.at( k ).mArrivalTime ) swap( uAllProcess.at( j ), uAllProcess.at( k ) ) ; 
		  } // else if  
        } // for
      } // for     	 	
      // 已經抵達 
      uAllProcess.at( i ).mNSJFWTime = count - uAllProcess.at( i ).mArrivalTime ; // Waiting的時間為排隊時間 
  	  for ( int burst = uAllProcess.at( i ).mCpuBurst ; burst > 0 ; burst--, count++ ) {
        // 執行uAllProcess、減少Burst time 
        char id = '\0' ;
        if ( uAllProcess.at( i ).mProcessID > 9 ) { // 10以上的數用英文字表示
          id = uAllProcess.at( i ).mProcessID + '7' ;
	    } // if
	    else {
          id = uAllProcess.at( i ).mProcessID + '0' ;
	    } // else 
        uNSJFGrantt = uNSJFGrantt + id ; // 放入甘特圖 
      } // for

      uAllProcess.at( i ).mNSJFTurnTime = uAllProcess.at( i ).mNSJFWTime + uAllProcess.at( i ).mCpuBurst  ; 
      // Turnaround time = waiting time + bursttime

    } // if 
    else {
      // 沒有uAllProcess抵達、累計Cycle 
      while( count < uAllProcess.at( i ).mArrivalTime ) {
      	uNSJFGrantt = uNSJFGrantt + "-" ;
        count = count + 1 ; 
      } // while

      i = i - 1 ; // 偵測到uAllProcess沒到把Count累加後、下次迴圈會變另一個、故-1變回原來的 
	} // else
 
  } // for

  // cout << uNSJFGrantt << endl ;
  // for ( int i = 0 ; i < uAllProcess.size() ; i++ ) cout << uAllProcess.at( i ).mNSJFWTime << endl ;; 
} // NSJFMethod()

void PSJFMethod() {
// Preemptive Shortest Job First( SRTF )
// preemptive
// 每當有新的Process進來，比對burst大小。 
// 剩餘的CPU Burst相同, 讓沒有用過CPU的先使用, 無法分別時則依arrival time小的先處理
// 若剩餘CPU Burst相同且arrival time相同, 則依ProcessID由小至大依序處理。  
// 但是當CPU裡process的CPU Burst等於ready佇列裡第一個process的CPU Burst，且備妥佇列裡第一個process尚未被使用並不會發生搶奪
  int CycleSum = 0 ; // 總共需要花多少時間
  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    // 依照ArrivalTime由小到大排序
    for( int j = i + 1 ; j < uAllProcess.size() ; j++ ) {
      if ( uAllProcess.at( i ).mArrivalTime < uAllProcess.at( j ).mArrivalTime ) {
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // if
      else if ( uAllProcess.at( i ).mArrivalTime == uAllProcess.at( j ).mArrivalTime ) {
       // 同時抵達、Priority小的放前面 
        if ( uAllProcess.at( i ).mPriority > uAllProcess.at( j ).mPriority )
          swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // else if
    } // for
  } // for

  for ( int i = 0 ; i < uAllProcess.size() ; i++ ) CycleSum = CycleSum + uAllProcess.at( i ).mCpuBurst ; 
  int count = 1 ; // Cycle、用來計算Turnaround、Waiting Time
  ProcessType RunProcess ;
  int NextArrivalProcess = 0 ; // 紀錄下一個需要放進去Queue的Process位址 
  vector< ProcessType > Process = uAllProcess ; 
  vector< ProcessType > ReadQueue ; // 準備佇列 
  while ( count <= CycleSum ) {

    // 將已經抵達的Process放入Queue中，不包含已經完成的Process 
    for( int i = 0 ; i < Process.size() ; i++ ) {
      if( Process.at( i ).mArrivalTime <= count && Process.at( i ).mCpuBurst != 0 && !Process.at( i ).inQueue ) {
        ReadQueue.push_back( Process.at( i ) ) ;
        Process.at( i ).inQueue = true ;
	  } // if
	} // for

    //for ( int i = 0 ; i < ReadQueue.size() ; i++ ) cout << ReadQueue.at(i).mProcessID << "-" <<ReadQueue.at(i).mCpuBurst << " ";
    //cout << endl << "------------------------"  << endl ; 
    // 將Queue排序
    for ( int i = 0 ; i < ReadQueue.size() ; i++ ) {
      for ( int j = i + 1 ; j < ReadQueue.size() ; j++ ) {
       // if ( ReadQueue.at( j ).mProcessID == 4 ) cout << ReadQueue.at( i ).beUsedtime << endl ; 
        if ( ReadQueue.at( j ).mCpuBurst == ReadQueue.at( i ).mCpuBurst 
			 && i == 0 && ReadQueue.at( i ).mProcessID == RunProcess.mProcessID
			 && !ReadQueue.at( j ).beUsed ) { // 特例 
		  // 判斷CPU裡的Process是不是還是上次的Proces 
          // 當CPU裡process的burst等於ready佇列裡第一個process的burst
		  // 備妥佇列裡第一個burst尚未被使用並不會發生搶奪
	    } // if
        else if ( ReadQueue.at( j ).mCpuBurst < ReadQueue.at( i ).mCpuBurst ) {
          // 已到達的Process，如果burst較小則先執行 
          swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ; 
	    } // else if
        else if ( ReadQueue.at( j ).mCpuBurst == ReadQueue.at( i ).mCpuBurst 
                  && ( !ReadQueue.at( j ).beUsed && ReadQueue.at( i ).beUsed ) ) {
          // 一個有用過一個沒用過，burst相同, 讓沒有用過CPU的先使用
          swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ; 
	    } // else if
	    else if ( ReadQueue.at( j ).mCpuBurst == ReadQueue.at( i ).mCpuBurst 
                  && ( !ReadQueue.at( j ).beUsed && !ReadQueue.at( i ).beUsed 
				  || ReadQueue.at( j ).beUsed && ReadQueue.at( i ).beUsed )   
                  && ReadQueue.at( j ).mArrivalTime < ReadQueue.at( i ).mArrivalTime ) {
	        // burst相同，且兩個都沒用過的或都用過，則早到的先執行 
          swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
		} // else if
        else if ( ReadQueue.at( j ).mCpuBurst == ReadQueue.at( i ).mCpuBurst 
                  && ( !ReadQueue.at( j ).beUsed && !ReadQueue.at( i ).beUsed 
				  || ReadQueue.at( j ).beUsed && ReadQueue.at( i ).beUsed )  
		          && ReadQueue.at( j ).mArrivalTime == ReadQueue.at( i ).mArrivalTime 
                  && ReadQueue.at( j ).mProcessID < ReadQueue.at( i ).mProcessID ) {
          // burst相同，且兩個都沒用過的或都用過、ArrivalTime相同，ProcessId小的排前面 
		  swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
        } // else if
 	  } // for
	} // for
 
     //for ( int i = 0 ; i < ReadQueue.size() ; i++ ) cout << ReadQueue.at(i).mProcessID << "-" <<ReadQueue.at(i).mCpuBurst << " ";
	 //cout << endl << endl << endl << endl ; 
    // 設定正在執行的Process、設定甘特圖
    if ( ReadQueue.size() > 0 ) {
      // 確保CPU有Process需要執行 
      for( int i = 0 ; i < Process.size() ; i++ ) {
        if( Process.at( i ).mProcessID == ReadQueue.front().mProcessID ) {
          Process.at( i ).mCpuBurst = Process.at( i ).mCpuBurst - 1 ; // 執行一個Cycle需要的time-1
          if ( !ReadQueue.front().beUsed ) ReadQueue.front().beUsedtime = count ; // 紀錄CPU使用過的時間
          ReadQueue.front().beUsed = true ; 
          ReadQueue.front().mCpuBurst = ReadQueue.front().mCpuBurst - 1 ;
          char id = '\0' ;
          if ( Process.at( i ).mProcessID > 9 ) { // 10以上的數用英文字表示
            id = Process.at( i ).mProcessID + '7' ;
	      } // if
    	  else {
            id = Process.at( i ).mProcessID + '0' ;
	      } // else 
          uPSJFGrantt = uPSJFGrantt + id ; // 放入甘特圖  
	    } // if
  	  } // for
      // 計算Waiting time  
      // ReadQueue裡除了第一個Process以外，都在Waiting、如果Arrival也就會在ReadyQueue中 
      for ( int i = 1 ; i < ReadQueue.size() ; i++ ) {
        for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
          if ( uAllProcess.at( j ).mProcessID == ReadQueue.at( i ).mProcessID ) {
            // 不放到Process直接放到uAllProcess 
            uAllProcess.at( j ).mPSJFWTime = uAllProcess.at( j ).mPSJFWTime + 1 ;
          } // if 
        } // for 
      } // for
      // 結束的Process從Queue移除
  	  RunProcess = ReadQueue.front()  ;
      if ( RunProcess.mCpuBurst == 0 ) {
        ReadQueue.erase( ReadQueue.begin() ) ;
	  } // if

    } // if
    else {
      // 如果CPU空閒，一樣紀錄甘特圖 
      uPSJFGrantt = uPSJFGrantt + "-" ;
 	  CycleSum++ ;
	} // else

    count++ ;
  } // while 

  // 計算Turnaround time  
  // Turnaroundtime = waiting time + burst time
  for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
    uAllProcess.at( j ).mPSJFTurnTime = uAllProcess.at( j ).mPSJFWTime + uAllProcess.at( j ).mCpuBurst ;
  } // for 

  // cout << uPSJFGrantt << endl ;
  //for ( int i = 0 ; i < uAllProcess.size() ; i++ ) cout << uAllProcess.at( i ).mPPWTime << endl ;; 
} // PJSFMethod()

void RRMethod() {
// RoundRobin
// preemptive
// 每當一個新的time slice，從queue最前面取出Process執行 
// Queue無排序情況
// 每新的一個Time slice才將Process移到後面 
  int CycleSum = 0 ; // 總共需要花多少時間 
  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    // 依照ArrivalTime由小到大排序
    for( int j = i ; j < uAllProcess.size() ; j++ ) {
      if ( uAllProcess.at( i ).mArrivalTime > uAllProcess.at( j ).mArrivalTime ) {
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // if
      else if ( uAllProcess.at( i ).mArrivalTime == uAllProcess.at( j ).mArrivalTime ) {
       // 同時抵達、burst小的放前面 
        if ( uAllProcess.at( i ).mProcessID > uAllProcess.at( j ).mProcessID )
          swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // else if  
    } // for
  } // for

  for ( int i = 0 ; i < uAllProcess.size() ; i++ ) CycleSum = CycleSum + uAllProcess.at( i ).mCpuBurst ; 
  int count = 1 ; // Cycle、用來計算Turnaround、Waiting Time
  int NextArrivalProcess = 0 ; // 紀錄下一個需要放進去Queue的Process位址 
  int cpuslice = 1 ; // 計算新的Process在CPU執行的時間，如果Process結束或timeout則歸零 
  ProcessType RunProcess ;
  vector< ProcessType > Process = uAllProcess ; 
  vector< ProcessType > ReadyQueue ; // 準備佇列 
  while ( count <= CycleSum ) {
    // 將已經抵達的Process放入Queue中，不包含已經完成的Process 
    for( int k = NextArrivalProcess ; k < Process.size() ; k++ ) {
      if( Process.at( k ).mArrivalTime <= count && Process.at( k ).mCpuBurst != 0 && !Process.at( k ).inQueue ) {
        ReadyQueue.push_back( Process.at( k ) ) ;
        Process.at( k ).inQueue = true ; 
        NextArrivalProcess = k + 1 ;
	  } // if
	} // for

    // 如果Process的timeslice到了卻同時有新的進來，需要先讓新的進QUEUE 
    if ( RunProcess.mCpuBurst != 0 && cpuslice == 1 && count != 1 ) ReadyQueue.push_back( RunProcess ) ; 

	if ( ReadyQueue.size() > 0 ) {
      // 設定正在執行的Process、設定甘特圖 
      for( int i = 0 ; i < Process.size() ; i++ ) {
        if( Process.at( i ).mProcessID == ReadyQueue.front().mProcessID ) {
          Process.at( i ).mCpuBurst = Process.at( i ).mCpuBurst - 1 ; // 執行一個Cycle需要的time-1 
          ReadyQueue.front().mCpuBurst = ReadyQueue.front().mCpuBurst - 1 ;
          char id = '\0' ;
          if ( Process.at( i ).mProcessID > 9 ) { // 10以上的數用英文字表示
            id = Process.at( i ).mProcessID + '7' ;
	      } // if
      	  else {
            id = Process.at( i ).mProcessID + '0' ;
	      } // else 
          uRRGrantt = uRRGrantt + id ; // 放入甘特圖  
	    } // if
	  } // for
    // 執行的Process如果到達Timeslice從Queue最前面放到最後面
	// 結束則從ReadyQueue最前面移除 
      RunProcess = ReadyQueue.front() ;
      if ( RunProcess.mCpuBurst == 0 || cpuslice == uTimeslice ) {
        ReadyQueue.erase( ReadyQueue.begin() ) ;
        cpuslice = 0 ; // 迎接新的Process 
  	  } // if 
      // 計算Waiting time  
      // ReadQueue裡除了第一個Process以外，都在Waiting、如果Arrival也就會在ReadyQueue中 
      for ( int i = 0 ; i < ReadyQueue.size() ; i++ ) {
        for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
          if ( uAllProcess.at( j ).mProcessID == ReadyQueue.at( i ).mProcessID && ReadyQueue.at( i ).mProcessID != RunProcess.mProcessID ) {
            // 不放到Process直接放到uAllProcess 
            uAllProcess.at( j ).mRRWTime = uAllProcess.at( j ).mRRWTime + 1 ;
          } // if 
        } // for 
      } // for

	  cpuslice = cpuslice + 1 ; 
	} // if 
	else {
	  // 若CPU閒置、一樣紀錄 
	  uRRGrantt = uRRGrantt + "-" ;
      CycleSum++ ;  
	} // else 
	
	count = count + 1 ;
  } // while 
  // 計算Turnaround time  
  // Turnaroundtime = waiting time + burst time
  for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
    uAllProcess.at( j ).mRRTurnTime = uAllProcess.at( j ).mRRWTime + uAllProcess.at( j ).mCpuBurst ;
  } // for 

  // cout << uRRGrantt << endl ;
  // for ( int i = 0 ; i < uAllProcess.size() ; i++ ) cout << uAllProcess.at( i ).mRRWTime << endl ;; 
} // RRMethod()

void PPMethod() {
// Priority
// preemptive
// 每當有新的Process進來，比對Priority大小。 
// 剩餘的Priority相同, 讓沒有用過CPU的先使用, 無法分別時則依arrival time小的先處理
// 若剩餘Priority相同且arrival time相同, 則依ProcessID由小至大依序處理。  
// 但是當CPU裡process的Priority等於ready佇列裡第一個process的Priority，且備妥佇列裡第一個process尚未被使用並不會發生搶奪
  int CycleSum = 0 ; // 總共需要花多少時間
  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    // 依照ArrivalTime由小到大排序
    for( int j = i + 1 ; j < uAllProcess.size() ; j++ ) {
      if ( uAllProcess.at( i ).mArrivalTime < uAllProcess.at( j ).mArrivalTime ) {
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // if
      else if ( uAllProcess.at( i ).mArrivalTime == uAllProcess.at( j ).mArrivalTime ) {
       // 同時抵達、Priority小的放前面 
        if ( uAllProcess.at( i ).mPriority > uAllProcess.at( j ).mPriority )
          swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // else if
    } // for
  } // for

  for ( int i = 0 ; i < uAllProcess.size() ; i++ ) CycleSum = CycleSum + uAllProcess.at( i ).mCpuBurst ; 
  int count = 1 ; // Cycle、用來計算Turnaround、Waiting Time
  ProcessType RunProcess ;
  int NextArrivalProcess = 0 ; // 紀錄下一個需要放進去Queue的Process位址 
  vector< ProcessType > Process = uAllProcess ; 
  vector< ProcessType > ReadQueue ; // 準備佇列 
  while ( count <= CycleSum ) {

    // 將已經抵達的Process放入Queue中，不包含已經完成的Process 
    for( int i = 0 ; i < Process.size() ; i++ ) {
      if( Process.at( i ).mArrivalTime <= count && Process.at( i ).mCpuBurst != 0 && !Process.at( i ).inQueue ) {
        ReadQueue.push_back( Process.at( i ) ) ;
        Process.at( i ).inQueue = true ;
	  } // if
	} // for

    // for ( int i = 0 ; i < ReadQueue.size() ; i++ ) cout << ReadQueue.at(i).mProcessID << "-" <<ReadQueue.at(i).beUsedtime << " ";
	// cout << endl << "------------------------"  << endl ; 
    // 將Queue排序
    if ( ReadQueue.size() > 0 ) {
      for ( int i = 0 ; i < ReadQueue.size() ; i++ ) {
        for ( int j = i + 1 ; j < ReadQueue.size() ; j++ ) { 
        // if ( ReadQueue.at( j ).mProcessID == 4 ) cout << ReadQueue.at( i ).beUsedtime << endl ; 
          /*if ( ReadQueue.at( j ).mPriority == ReadQueue.at( i ).mPriority 
		        && i == 0 && ReadQueue.at( i ).mProcessID == RunProcess.mProcessID ) {
		    // 判斷CPU裡的Process是不是還是上次的Proces 
            // 當CPU裡process的Priority等於ready佇列裡第一個process的Priority
		    // 備妥佇列裡第一個process尚未被使用並不會發生搶奪
	      } // if
          else if ( ReadQueue.at( j ).mPriority < ReadQueue.at( i ).mPriority ) {
            // 已到達的Process，如果Priority較小則先執行 
            swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ; 
	      } // else if
          else if ( ReadQueue.at( j ).mPriority == ReadQueue.at( i ).mPriority 
                    && ( !ReadQueue.at( j ).beUsed && ReadQueue.at( i ).beUsed ) 
				    && ReadQueue.at( i ).beUsedtime > ReadQueue.at( j ).beUsedtime ) {
            // 一個有用過一個沒用過，Priority相同, 讓沒有用過CPU的先使用
            swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ; 
	      } // else if
	      else if ( ReadQueue.at( j ).mPriority == ReadQueue.at( i ).mPriority 
	                && ( !ReadQueue.at( j ).beUsed && !ReadQueue.at( i ).beUsed || ReadQueue.at( j ).beUsed && ReadQueue.at( i ).beUsed ) 
                    && ReadQueue.at( j ).mArrivalTime < ReadQueue.at( i ).mArrivalTime ) {
	          // Priority相同，且兩個都用過或都沒用過，則早到的先執行 
            swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
		  } // else if
          else if ( ReadQueue.at( j ).mPriority == ReadQueue.at( i ).mPriority 
	                && ( !ReadQueue.at( j ).beUsed && !ReadQueue.at( i ).beUsed || ReadQueue.at( j ).beUsed && ReadQueue.at( i ).beUsed )  
		            && ReadQueue.at( j ).mArrivalTime == ReadQueue.at( i ).mArrivalTime 
                    && ReadQueue.at( j ).mProcessID < ReadQueue.at( i ).mProcessID ) {
            // Priority相同，且兩個都用過或都沒用過、ArrivalTime相同，ProcessId小的排前面 
		    swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
          } // else if*/
		  if ( i == 0 && ReadQueue.at( i ).mProcessID == RunProcess.mProcessID ) {
		    // 修改題不搶奪 
	      } // if
          else if ( ReadQueue.at( j ).mPriority < ReadQueue.at( i ).mPriority ) {
            // 已到達的Process，如果Priority較小則先執行 
            swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ; 
	      } // if
	      else if ( ReadQueue.at( j ).mPriority == ReadQueue.at( i ).mPriority 
                    && ReadQueue.at( j ).mArrivalTime < ReadQueue.at( i ).mArrivalTime ) {
	          // Priority相同，且兩個都用過或都沒用過，則早到的先執行 
            swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
		  } // else if
          else if ( ReadQueue.at( j ).mPriority == ReadQueue.at( i ).mPriority  
		            && ReadQueue.at( j ).mArrivalTime == ReadQueue.at( i ).mArrivalTime 
                    && ReadQueue.at( j ).mProcessID > ReadQueue.at( i ).mProcessID ) {
            // Priority相同，且兩個都用過或都沒用過、ArrivalTime相同，ProcessId小的排前面 
		    swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
          } // else if
 	    } // for
	  } // for
       // for ( int i = 0 ; i < ReadQueue.size() ; i++ ) cout << ReadQueue.at(i).mProcessID << "-" <<ReadQueue.at(i).beUsedtime << " ";
	   // cout << endl << endl << endl << endl ; 
      // 設定正在執行的Process、設定甘特圖
      for( int i = 0 ; i < Process.size() ; i++ ) {
        if( Process.at( i ).mProcessID == ReadQueue.front().mProcessID ) {
          Process.at( i ).mCpuBurst = Process.at( i ).mCpuBurst - 1 ; // 執行一個Cycle需要的time-1
          if ( !ReadQueue.front().beUsed ) ReadQueue.front().beUsedtime = count ; // 紀錄CPU使用過的時間
          ReadQueue.front().beUsed = true ; 
          ReadQueue.front().mCpuBurst = ReadQueue.front().mCpuBurst - 1 ;
          char id = '\0' ;
          if ( Process.at( i ).mProcessID > 9 ) { // 10以上的數用英文字表示
            id = Process.at( i ).mProcessID + '7' ;
	      } // if
          else {
            id = Process.at( i ).mProcessID + '0' ;
	      } // else 
          uPPGrantt = uPPGrantt + id ; // 放入甘特圖  
	    } // if
	  } // for

      // 計算Waiting time  
      // ReadQueue裡除了第一個Process以外，都在Waiting、如果Arrival也就會在ReadyQueue中 
      for ( int i = 1 ; i < ReadQueue.size() ; i++ ) {
        for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
          if ( uAllProcess.at( j ).mProcessID == ReadQueue.at( i ).mProcessID ) {
            // 不放到Process直接放到uAllProcess 
            uAllProcess.at( j ).mPPWTime = uAllProcess.at( j ).mPPWTime + 1 ;
          } // if 
        } // for 
      } // for
      // 結束的Process從Queue移除
  	  RunProcess = ReadQueue.front()  ;
      if ( RunProcess.mCpuBurst == 0 ) {
        ReadQueue.erase( ReadQueue.begin() ) ;
  	  } // if
	} // if
	else {
	  // 若CPU為閒置，一樣紀錄 
      uPPGrantt = uPPGrantt + "-" ;	
      CycleSum++ ;
	} // else 

    count++ ;
  } // while 

  // 計算Turnaround time  
  // Turnaroundtime = waiting time + burst time
  for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
    uAllProcess.at( j ).mPPTurnTime = uAllProcess.at( j ).mPPWTime + uAllProcess.at( j ).mCpuBurst ;
  } // for 

  // cout << uPPGrantt << endl ;
  //for ( int i = 0 ; i < uAllProcess.size() ; i++ ) cout << uAllProcess.at( i ).mPPWTime << endl ;; 
} // PPMethod()

int main(int argc, char** argv) {

  string filename = "" ;
  cin >> filename ; // 讀取檔案名稱
  filename = filename + ".txt" ;
  file.open( filename.c_str(), ios::in ) ;
  while( !file ) { // 防呆 
    cin >> filename ; // 讀取檔案名稱
    filename = filename + ".txt" ;
    file.open( filename.c_str(), ios::in ) ;
    cout << "Wrong FileName" << endl ;
  } // while 

  // 第一行第一個integer為method,範圍1~6
  string line = "" ;
  int method = 0 ;
  getline( file, line ) ;
  istringstream ss( line ) ;
  ss >> method ;   // stirng轉成Int型別
  // 第一行第二個integer為time slice,範圍不定
  ss >> uTimeslice ;  // stirng轉成Int型別

  StoreProcess() ; // 將process資料存到uAllProcess中 

  switch( method ) {

    case 1 : // FCFS
      FCFSMethod() ; 
      WriteFile( 1, filename ) ;
    break ;
    case 2 : // NSJF
      NSJFMethod() ;
      WriteFile( 2, filename ) ;
    break ;
    case 3 : // PSJF
      PSJFMethod() ;
      WriteFile( 3, filename ) ;
    break ;
    case 4 : // RR
      RRMethod() ;
      WriteFile( 4, filename ) ;
    break ;
    case 5 : // PP
      PPMethod() ;
      WriteFile( 5, filename ) ;
    break ;
    case 6 : // 全部
      FCFSMethod() ; 
      NSJFMethod() ;
      PSJFMethod() ;
      RRMethod() ;
      PPMethod() ;
      WriteFile( 6, filename ) ;
    break ;
    default:
      cout << "Wrong Method" ;
    break ;
  } // switch

  return 0;
} // main 


