# include <iostream> // cin cout
# include <string>
# include <cstring>
# include <fstream>
# include <cstdlib> // atoi ��ƩҦb�禡�w
# include <queue>
# include <map>
# include <utility>
using namespace std ;


class Template {
    public:
            pair <int, int> p;
        char **test = NULL ;
        bool **right = NULL ;
        bool **V = NULL ;

            map < pair<int,int>, pair<int,int> > m ;
            queue < pair<int,int> > q ;
        int row = 0, list = 0 ;

        void ArrayGet() { // ------------------------------------------------------------------- Ū�i.txt�ɸ̪����  �s�i�G���}�C
            string str, filenum, numstr ;
            fstream file;
            bool error = false ;
            do {
                error = false ;
                cout << endl << "Input a file number (e.g., 201, 202, ...): " ;
                cin >> filenum ;
                 str = "Input" + filenum + ".txt" ;

                file.open( str.c_str(), ios::in ) ;
                if( !file ) {                                                       //�ˬd�ɮ׬O�_���\�}��
                    cerr << "input" << filenum << ".txt does not exist!" << endl ;  // ���b
                    error = true ;
                }
            } while ( error ) ;

            file >> numstr ;
            list = atoi( numstr.c_str() ) ; // Get list
            file >> numstr ;
            row = atoi( numstr.c_str() ) ;    // Get Row

            test = new char*[row] ;         // �B�z�ʺA�}�C
            right = new bool*[row] ;
            V = new bool*[row] ;
            for ( int i = 0 ; i < row ; i++ ) {
                test[i] = new char[list] ;
                right[i] = new bool[list] ;
                V[i] = new bool[list] ;
                file >> test[i] ;
            } // for

            for (int i = 0 ; i < row ; i++) {
                for ( int j = 0 ; j < list ; j++ ) {
                    V[i][j] = false ;
                    right[i][j] = false ;
                }
            }

            q.push({0,0}) ;



            file.close() ;
        } // ArrayGet()

        bool over ( int i, int j ) { // -------------------------------------------------------- �P�_�g�c���
            return i >= 0 && i < row && j >= 0 && j < list ;
        } // over

        bool Walk( int i, int j, int &times, bool &rigthRoad ) { // ---------------------------- �ѹ������ʭy��
            bool finish = false ;
            if ( over( i+1, j ) && test[i+1][j] == 'G' ) {               // �ˬd�U���O���OG
                  test[i+1][j] = 'X' ; // �⨫�L��G ����X
                times-- ;
                if ( times != 0 ) {
                    finish = Walk( i+1, j, times, rigthRoad ) ;
                    rigthRoad = true ;
                } // if
                  else return true ;
            } // if
            if ( over( i, j-1 ) && test[i][j-1] == 'G' ) {               // �ˬd����O���OG
                test[i][j-1] = 'X' ;
                times-- ;
                if ( times != 0 ) {
                    finish = Walk( i, j-1, times, rigthRoad ) ;
                    rigthRoad = true ;
                }
                  else return true ;
            } // if
            if ( over( i-1, j ) && test[i-1][j] == 'G' ) {                // �ˬd�W���O���OG
                test[i-1][j] = 'X' ;
                times-- ;
                if ( times != 0 ) {
                    finish = Walk( i-1, j, times, rigthRoad ) ;
                    rigthRoad = true ;
                }
                  else return true ;
            } // if
            if ( over( i, j+1 ) && test[i][j+1] == 'G' ) {               // �ˬd�k��O���OG
                test[i][j+1] = 'X' ; // �⨫�L��G �令 X
                times-- ;
                if ( times != 0 ) {
                    finish = Walk( i, j+1, times, rigthRoad ) ;
                    rigthRoad = true ;
                }
                  else return true ;
            } // if
              else {
                if( over( i, j+1 ) && test[i][j+1] == 'E' && !finish ) { // �ˬd�k��i���i�H��
                      test[i][j+1] = 'V' ;
                      right[i][j+1] = true ;
                      finish = Walk( i, j+1, times, rigthRoad ) ;
                      if ( !finish && !rigthRoad ) right[i][j+1] = false ;
                  } // if
                  if( over( i+1, j ) && test[i+1][j] == 'E' && !finish ) { // �ˬd�U���i���i�H��
                      test[i+1][j] = 'V' ;
                      right[i+1][j] = true ;
                      finish = Walk( i+1, j, times, rigthRoad ) ;
                      if ( !finish && !rigthRoad ) right[i+1][j] = false ;
                } // if
                if( over( i, j-1 ) && test[i][j-1] == 'E' && !finish ) { // �ˬd����i���i�H��
                      test[i][j-1] = 'V' ;
                      right[i][j-1] = true ;
                      finish = Walk( i, j-1, times, rigthRoad ) ;
                      if ( !finish && !rigthRoad ) right[i][j-1] = false ;
                  } // if
                   if( over( i-1, j ) && test[i-1][j] == 'E' && !finish ) { // �ˬd�W���i���i�H��
                       test[i-1][j] = 'V' ;
                       right[i-1][j] = true ;
                       finish = Walk( i-1, j, times, rigthRoad ) ;
                       if ( !finish && !rigthRoad ) right[i-1][j] = false ;
                  } // if
            } // else

               if ( !finish ) return false ;
               else return true ;
         } // Walk()

        bool Is_num ( int &num ) { // ------------------------------------------------------------- ���b (�ư��Ʀr�H�~����J)
              string numstr ;
               cin >> numstr ;
            if ( numstr == "0" ) { // ��J������0
                 num = 0 ;
                   return true ;
             } // if

              num = atoi(numstr.c_str()) ;
              if ( num == 0 ) return false ;
              else return true ;
        } // Is_num()

        void output( int row, int list, bool FindG ) { // ----------------------------------------- �L�X���G
            for ( int i = 0 ; i < row ; i++ ) {
                 for ( int  j = 0 ; j < list ; j++ ) {
                     if ( test[i][j] == 'G'  || test[i][j] == 'X' ) cout << "G" ;
                     else cout << test[i][j] ;
                 } // for
                 cout << endl ;
             } // for

            if ( FindG ) {
                cout << endl ;
                for ( int i = 0 ; i < row ; i++ ) {
                     for ( int  j = 0 ; j < list ; j++ ) {
                         if ( test[i][j] == 'O' ) cout << "O" ;
                         else if ( test[i][j] == 'G'  || test[i][j] == 'X' ) cout << "G" ;
                         else {
                             if ( right[i][j] ) cout << "R" ;
                             else cout << "E" ;
                        } // else
                       } // for
                       cout << endl ;
                 } // for
             } // if
             cout << endl ;
        } // Output()
        void Output_3 ( bool ShortG ) { //-------------�L�X�D�ԤT�����G�A��V[][]�Mright[][]�P�_V�MR
            for ( int i = 0 ; i < row ; i++ ) {
                     for ( int  j = 0 ; j < list ; j++ ) {
                         if ( test[i][j] == 'O' ) cout << "O" ;
                         else if ( test[i][j] == 'G' ) cout << "G" ;
                         else {
                             if ( V[i][j] ) cout << "V" ;
                             else cout << "E" ;
                        } // else
                       } // for
                       cout << endl ;
                 } // for
                 cout << endl ;
                 if ( ShortG ) {
                     right[0][0] = true ;
                 for ( int i = 0 ; i < row ; i++ ) {
                     for ( int  j = 0 ; j < list ; j++ ) {
                         if ( test[i][j] == 'O' ) cout << "O" ;
                         else if ( test[i][j] == 'G'  || test[i][j] == 'X' ) cout << "G" ;
                         else {
                             if ( right[i][j] ) cout << "R" ;
                             else cout << "E" ;
                        } // else
                       } // for
                       cout << endl ;
                 } // for
             } // if
                 cout << endl ;
        }
        void FindR( pair<int,int> now ) { // ----------------------------------------------��map�NR�����|�O���bright[][]��
            for ( pair<int,int> i = now ; !(i.first == 0 && i.second == 0) ; i = m[i] ){
                    right[i.first][i.second] = true ;
            } // for
            right[0][0] = true ;
        }

        bool Mission3() { // -------------------------------------------------�D�ԤT
                 if ( q.empty() ) return false ; // �䤣��^��false
                 pair<int,int> now ;
                 pair<int,int> next ;

                 now = q.front() ;
                 next = make_pair( now.first, now.second ) ;
                 int i = now.first ;
                 int j = now.second ;

                 q.pop() ;

                 if ( over( i, j ) && test[i][j] == 'G' ) { // ���G�^��true
                        FindR( now ) ;
                        return true ;
                 }

                 if(  over( i, j+1 ) && ( test[i][j+1] == 'E'  || test[i][j+1] == 'G' ) ) { // �N�I�P��ਫ����l�O�bq���A�s�bm��
                         if( !V[i][j+1] ) {
                             next = make_pair( now.first, now.second+1 ) ;
                              m[next] = now ;
                              q.push(next) ;
                         } // if

                 } // if
                 if( over( i+1, j ) && ( test[i+1][j] == 'E'  || test[i+1][j] == 'G' ) ) { 
                         if ( !V[i+1][j] ) {
                             next = make_pair( now.first+1, now.second ) ;
                             m[next] = now ;
                             q.push(next) ;
                         } // if

                 } // if
                 if( over( i, j-1 ) && ( test[i][j-1] == 'E'  || test[i][j-1] == 'G' ) ) { 
                         if ( !V[i][j-1] ) {
                             next = make_pair( now.first, now.second-1 ) ;
                             m[next] = now ;
                             q.push(next) ;
                         } // if

                 } // if
                 if( over( i-1, j ) && ( test[i-1][j] == 'E'  || test[i-1][j] == 'G' ) ) { 
                         if ( !V[i-1][j] ) {
                             next = make_pair( now.first-1, now.second ) ;
                             m[next] = now ;
                             q.push(next) ;
                         } // if

                 } // if

                 V[i][j] = true ; // --------------�N�o�@��O��V

                 return Mission3() ; // -------���j

            } // Mission3
} ;

int main() {
    while ( true ) {
          cout << "*** Path Finding ***" << endl ;
           cout << "* 0. Quit          *" << endl ;
        cout << "* 1. One goal      *" << endl ;
        cout << "* 2. More goals    *" << endl ;
        cout << "* 3. Shortest path *" << endl ;
        cout << "********************" << endl ;
        cout << "Input a command(0, 1, 2, 3): " ;
        Template maze ;

        int command ;
        if ( !maze.Is_num( command ) ) cout << "Command does not exist!" << endl << endl ;
        else if ( command > 3 || command < 0 ) cout << "Command does not exist!" << endl << endl ;
        else if ( command == 0 ) break ;
        else {
              maze.ArrayGet() ; // --------------------------------------------------- Get Array

              int times = 1 ;
              bool rigthRoad = false ;
              maze.test[0][0] = 'V' ; // --------------------------------------------- test[]�Ĥ@����]��V
               maze.right[0][0] = true ; // ------------------------------------------- right[]�Ĥ@����]��true
              if ( command == 1 ) {
                bool FindG = maze.Walk( 0,0, times, rigthRoad ) ; // --------------- �O�_�����G
                maze.output( maze.row, maze.list, FindG ) ;
            } // if
            else if( command == 2 ) {
                do {
                    cout << endl << "Number of G (goals): " ;
                    if ( maze.Is_num( times ) && ( times > 100 || times < 1 ) )
                        cout << endl << "### The number must be in [1,100] ###" << endl ;
                } while ( times > 100 || times < 1 ) ;

                bool FindGs = maze.Walk( 0, 0, times, rigthRoad ) ; // ------------- �O�_����쥿�T�ƶq��G
                maze.output( maze.row, maze.list, FindGs ) ;
            } // else if
            else if ( command == 3 ) {
                bool ShortG = false ;
                    ShortG = maze.Mission3( ) ; // --------------- �O�_�����̵u���|G
                    maze.Output_3( ShortG ) ;
            } // if
          } // else
      } // while
} // main()

