!-------------------------------------------------------
!Name: Ethan Coles
!ID: 0843081
!File: tictactoe.f95
!Description: CIS*3190 Assignment 1, Tictactoe using Fortran.
!-------------------------------------------------------

!main program
program tictactoe
  character (len=1), dimension(3,3) :: tictac, winner !data structure for storing the board in a 3x3 2d array
  logical :: over

  tictac = reshape((/' ',' ',' ',' ',' ',' ',' ',' ',' '/),(/3,3/))

  write (*,*) 'PLAY TIC-TAC-TOE. ENTER 1-9 TO PLAY'
  write (*,*) ' 1 | 2 | 3 '
  write (*,*) '---+---+---'
  write (*,*) ' 4 | 5 | 6 '
  write (*,*) '---+---+---'
  write (*,*) ' 7 | 8 | 9 '
  write (*,*) ''

  do
    call playtictactoe(tictac)
    call showboard(tictac)
    
    !check if player won
    call chkovr(tictac, over, winner)
    if(over) then
      exit
    end if
    
    !perform computer move
    call pickmove(tictac)
    call showboard(tictac)
    
    !check if computer won
    call chkovr(tictac, over, winner)
    if(over) then
      exit
    end if
  end do

  select case(winner(1,1))
    case('X')
      write (*,*) 'YOU WIN'
    case('O')
      write (*,*) 'COMPUTER WINS'
    case('D')
      write (*,*) 'DRAW'
  end select
end program tictactoe

!functions and subroutines
!plays the game tic tac toe
subroutine playtictactoe(tictac)
  character (len=1), dimension(3,3) :: tictac
  integer :: getmove
  integer :: move !value representing which postion the player chose to place X

  do
    move = getmove(tictac)

    if(move /= 0) then !if input was invalid, attempt again
      exit
    end if
  end do

  write (*,*) ''
  write (*,*) 'After your move...'
  
  select case(move)
    case(1)
      tictac(1,1) = 'X'
    case(2)
      tictac(1,2) = 'X'
    case(3)
      tictac(1,3) = 'X'
    case(4)
      tictac(2,1) = 'X'
    case(5)
      tictac(2,2) = 'X'
    case(6)
      tictac(2,3) = 'X'
    case(7)
      tictac(3,1) = 'X'
    case(8)
      tictac(3,2) = 'X'
    case(9)
      tictac(3,3) = 'X'
  end select
end subroutine

!performs the player's moveand validates its input
!returns 1-9 on success, 0 on failure to attempt again
integer function getmove(tictac)
  character (len=1), dimension(3,3) :: tictac
  integer :: move
  logical :: chkplay

  write (*,*) 'Your move? (1-9)'
  read (*,*) move

  if(move >= 1 .and. move <= 9) then
    if(chkplay(tictac, move)) then !check if the choice is occupied
      getmove = move
    else
      getmove = 0
      write (*,*) 'Error: Square already occupied.'
    end if
  else
    getmove = 0
    write (*,*) 'Error: Invalid move. Enter a number between 1 and 9.'    
  end if
  
  return
end function getmove

!performs the computer's move
subroutine pickmove(tictac)
  character (len=1), dimension(3,3) :: tictac
  integer, dimension(1:8) :: sum = 0 !1-d array on size 8 containing the sums of each row, column, and diagonal
  integer :: i, j, tmp, rndmove !tmp computes the temporary sum to store in the sum array
  logical :: rndnum;
  logical :: chkplay

  write (*,*) ''
  write (*,*) 'After my move...'
  rndnum = .true. !assume the computer is making a random move

  !sum up rows
  tmp = 0;
  do i = 1,3
    do j = 1,3
      if(tictac(i,j) == 'O') then
        tmp = tmp + 4
      else if(tictac(i,j) == 'X') then
        tmp = tmp + 1
      end if
    end do

    sum(i) = tmp !indexes 1-3 stores sums of colums
    tmp = 0
  end do

  !sum up columns
  tmp = 0;
  do i = 1,3
    do j = 1,3
      if(tictac(j,i) == 'O') then
        tmp = tmp + 4
      else if(tictac(j,i) == 'X') then
        tmp = tmp + 1
      end if
    end do

    sum(i+3) = tmp !indexes 4-6 stores sums of colums
    tmp = 0
  end do

  !sum up diagonal #1
  tmp = 0;
  do i = 1,3
    if(tictac(i,i) == 'O') then
      tmp = tmp + 4
    else if(tictac(i,i) == 'X') then
      tmp = tmp + 1
    end if

    sum(7) = tmp !index 7 stores sum of diagonal #1
  end do

  !sum up diagonal #2
  tmp = 0;
  do i = 1,3
    if(tictac(i,4-i) == 'O') then
      tmp = tmp + 4
    else if(tictac(i,4-i) == 'X') then
      tmp = tmp + 1
    end if

    sum(8) = tmp !index 8 stores sum of diagonal #2
  end do

  !determine computer move based on collected sums
  !check potential win for computer to win game
  do i = 1,8
    if(sum(i) == 8) then
      call findblank(tictac, i)
      rndnum = .false.
      return
    end if
  end do

  !check potential win for player to prevent from winning
  do i = 1,8
    if(sum(i) == 2) then
      call findblank(tictac, i)
      rndnum = .false.
      return
    end if
  end do

  !otherwise, place in random square that is not occupied
  if(rndnum) then
    do
      rndmove = int(rand(0)*9)+1 !returns an random integer between 1 and 9
  
      if(chkplay(tictac,rndmove)) then
        exit
      end if
    end do

    select case(rndmove)
      case(1)
        tictac(1,1) = 'O'
      case(2)
        tictac(1,2) = 'O'
      case(3)
        tictac(1,3) = 'O'
      case(4)
        tictac(2,1) = 'O'
      case(5)
        tictac(2,2) = 'O'
      case(6)
        tictac(2,3) = 'O'
      case(7)
        tictac(3,1) = 'O'
      case(8)
        tictac(3,2) = 'O'
      case(9)
        tictac(3,3) = 'O'
    end select
  end if
end subroutine

!finds and places the computer's move in the blank space of a given rown, column, or diagonal
subroutine findblank(tictac, index)
  character (len=1), dimension(3,3) :: tictac
  integer :: index, k !index represents which row, column, or diagonal the sum occured in from pickmove()

  !in row
  if(index >= 1 .and. index <= 3) then
    do k = 1,3
      if(tictac(index,k) == ' ') then
        tictac(index,k) = 'O'
      end if
    end do

  !in column
  else if(index >= 4 .and. index <= 6) then
    do k = 1,3
      if(tictac(k,index-3) == ' ') then
        tictac(k,index-3) = 'O'
      end if
    end do

  !in diagonal#1
  else if(index == 7) then
    do k = 1,3
      if(tictac(k,k) == ' ') then
        tictac(k,k) = 'O'
      end if
    end do

  !in diagonal#2
  else if(index == 8) then
    do k = 1,3
      if(tictac(k,4-k) == ' ') then
        tictac(k,4-k) = 'O'
      end if
    end do
  end if
end subroutine

!outputs the current board each time a move is made
subroutine showboard(tictac)
  character (len=1), dimension(3,3) :: tictac
  1 format(2X,A,1X,'|',1X,A,1X'|'1X,A,1X)

  write (*,1) tictac(1,1), tictac(1,2), tictac(1,3)    
  write (*,*) '---+---+---'
  write (*,1) tictac(2,1), tictac(2,2), tictac(2,3)    
  write (*,*) '---+---+---'
  write (*,1) tictac(3,1), tictac(3,2), tictac(3,3)
  write (*,*) ''
end subroutine

!tests a row, column, or diagonal if all 3 are the same
logical function same(s1,s2,s3)
  character :: s1, s2, s3

  if(s1 == 'X' .and. s2 == 'X' .and. s3 == 'X') then
    same = .true.
  else if(s1 == 'O' .and. s2 == 'O' .and. s3 == 'O') then
    same = .true.
  else
    same = .false.
  end if

  return
end function same

!checks to make sure the human player cannot make a play in a square that is already occupied
logical function chkplay(tictac,move)
  character (len=1), dimension(3,3) :: tictac
  integer :: move
  
  if(move == 1 .and. tictac(1,1) == ' ') then 
    chkplay = .true.  
  else if(move == 2 .and. tictac(1,2) == ' ') then
    chkplay = .true.  
  else if(move == 3 .and. tictac(1,3) == ' ') then
    chkplay = .true.  
  else if(move == 4 .and. tictac(2,1) == ' ') then
    chkplay = .true.  
  else if(move == 5 .and. tictac(2,2) == ' ') then
    chkplay = .true.  
  else if(move == 6 .and. tictac(2,3) == ' ') then
    chkplay = .true.  
  else if(move == 7 .and. tictac(3,1) == ' ') then
    chkplay = .true.  
  else if(move == 8 .and. tictac(3,2) == ' ') then
    chkplay = .true.  
  else if(move == 9 .and. tictac(3,3) == ' ') then
    chkplay = .true.
  else
    chkplay = .false.
  end if
end function chkplay

!check if tic-tac-toe is over and determine winner (if any)
subroutine chkovr(tictac, over, winner)
  !argument definitions --
  !input arguments
  !tictac - represents the current state of the board game
  !output arguments
  !over - indicates whether or not game is over
  !winner - indicates the winner (O or X) or a draw (D)

  character (len=1), dimension(3,3) :: tictac, winner
  logical :: over
  
  !subroutine parameters
  character :: blank, draw
  parameter (blank = ' ', draw = 'D')

  !functions used
  logical :: same

  !local variables
  logical :: diagSame
  integer :: rowIndex, colIndex
  
  !assume game is over at start
  over = .true.

  !check for a winner
  !check rows for a winner
  do rowIndex=1, 3
    if (same(tictac(rowIndex,1), tictac(rowIndex,2), tictac(rowIndex,3))) then
      winner = tictac(rowIndex,1)
      return
    endif
  end do
  
  !no winner by rows, check columns for a winner
  do colIndex=1, 3
    if (same(tictac(1,colIndex), tictac(2,colIndex), tictac(3,colIndex))) then
      winner = tictac(1,colIndex)
    return
    endif
  end do
  
  !no winner by rows or columns, check diagonals for a winner
  diagSame = same(tictac(1,1), tictac(2,2), tictac(3,3)) &
  .or. same(tictac(1,3), tictac(2,2), tictac(3,1))
  if (diagSame) then
    winner = tictac(2,2)
    return
  end if
  
  !no winner at all. see if game is a draw
  !check each row for an empty space
  do ir = 1, 3
    do ic = 1, 3  
      if (tictac(ir,ic) .eq. blank) then
        over = .false.
        return
      end if  
    end do
  end do

  !no blank found, game is a draw
  winner = draw
  return
end subroutine
