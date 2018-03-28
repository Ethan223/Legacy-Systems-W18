!-------------------------------------------------------
!Name: Ethan Coles
!ID: 0843081
!File: sieve.f95
!Description: CIS*3190 Assignment 4, Fortran implentation
!of Sieve of Eratosthenes algorithm.
!-------------------------------------------------------
program sieve
    integer, allocatable :: numberset(:)
    integer :: limit
    integer :: i, j
    character (len=20) :: filename
    character (len=10) :: numformat
    logical :: exists

    
    !File name prompt
    write(*,'(a)') 'Enter file name to output prime numbers to: '
    read(*,*) filename
    inquire(file=filename, exist=exists)
    
    !Does the filename entered already exist
    if(exists) then
        write(*,'(a)') 'Error: File exists'
        stop
    end if

    
    !TODO: validate input
    write(*,'(a)') 'Enter a limit: '
    read(*,*) limit

    if(limit < 2 .or. limit > 1000000) then
        write(*,'(a)') 'Error: Invalid limit'
        stop
    else
        allocate(numberset(2:limit))
    end if
        

    do i = 2,limit
        numberset(i) = i
    end do

    do i = 2,limit
        if(numberset(i) /= 0) then
            do j = i+1,limit
                if(numberset(i) /= 0 .and. mod(numberset(j), numberset(i)) == 0) then
                    numberset(j) = 0
                end if
            end do
        end if
    end do

    
    !Output prime numbers to file
    open(unit=9, file=filename, status='new', action='write')

    do i = 2,limit
        if(numberset(i) /= 0) then
            1 format(I10)
            write(numformat,1) numberset(i)
            write(9,'(a)') adjustl(numformat)
        end if
    end do
    
    close(9, status='keep')
end program sieve