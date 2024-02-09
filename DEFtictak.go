package main

import (
	"fmt"
)

// Количество возможных ходов(test)
func number_possible_moves(array [3][3]string, sim string, glubina int) int {
	if win(array) == "x" || win(array) == "0" || win(array) == "Draft" {
		field(array)
		fmt.Print("\nПобедная глубина:", glubina)
		fmt.Println(" Победитель:", win(array))
		return 1
	}
	ps := possibl_move(array, sim)
	sum := 0
	for i := 0; i < len(ps); i++ {
		k := number_possible_moves(ps[i], posledova(sim), glubina+1)
		sum += k
	}
	debug(ps)
	fmt.Print("\nКоличество ходов:", sum)
	fmt.Println(" Глубина:", glubina)

	return sum
}

func max(x, y int) int {
	if x < y {
		x = y
	}
	return x
}
func min(x, y int) int {
	if x > y {
		x = y
	}
	return x
}
func reduce(array []int, f func(int, int) int) int {
	num := array[0]
	for i := 1; i < len(array); i++ {
		num = f(num, array[i])
	}
	return num
}

// счетчик победы в линию
func vin_count_line(array [3][3]string, sim string, line int) int {
	win := 0
	for i := 0; i < 3; i++ {
		if array[line][i] == sim {
			win = win + 1
		} else {
			break
		}
	}
	return win

}

// счетчик победы в столбик
func vin_count_column(array [3][3]string, sim string, stolb int) int {
	win := 0
	for i := 0; i < 3; i++ {
		if array[i][stolb] == sim {
			win = win + 1
		} else {
			break
		}
	}
	return win
}

// Проверка на победу
func win(pole [3][3]string) string {
	// Проверка строк
	win := 0
	for i := 0; i < 3; i++ {
		win = vin_count_line(pole, pole[i][0], i)
		if win == 3 {
			if pole[i][0] == "x" {
				return "x"
			}
			if pole[i][0] == "0" {
				return "0"
			}
		}
	}
	// Проверка столбиков
	for i := 0; i < 3; i++ {
		win = vin_count_column(pole, pole[0][i], i)
		if win == 3 {
			if pole[0][i] == "x" {
				return "x"
			}
			if pole[0][i] == "0" {
				return "0"
			}
		}
	}

	//Проверка диагоналей
	if (pole[0][0] == pole[1][1] && pole[2][2] == pole[1][1]) || (pole[0][2] == pole[1][1] && pole[2][0] == pole[1][1]) {
		if pole[1][1] == "x" {
			return "x"
		}
		if pole[1][1] == "0" {
			return "0"
		}
	}
	for !is_full(pole) {
		return "continue"
	}
	return "Draft"

}

// Проверка на заполненность поля
func is_full(array [3][3]string) bool {
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			if array[i][j] == "_" {
				return false
			}
		}
	}
	return true
}

// Возможные ходы.
func possibl_move(array [3][3]string, sim string) [][3][3]string {
	pos := [][3][3]string{}
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			if array[i][j] == "_" {
				array[i][j] = sim
				pos = append(pos, array)
				debug(pos)
				array[i][j] = "_"
			}
		}
	}
	return pos
}

// функция для просмотра возможных полей вывод в столб(test)
func posmov(pos [][3][3]string) {
	for i := 0; i < len(pos); i++ {
		fmt.Println()
		for j := 0; j < 3; j++ {
			//fmt.Println()
			for k := 0; k < 3; k++ {
				fmt.Printf("%2s", pos[i][j][k])
			}
		}
	}
}

// функция для просмотра дебага вывод в строку
func debug(dbg [][3][3]string) {
	for i := 0; i < 3; i++ {
		fmt.Println()
		for j := 0; j < len(dbg); j++ {
			if j != 0 {
				fmt.Print("|")
			}
			for k := 0; k < 3; k++ {
				fmt.Printf("%2s", dbg[j][i][k])
			}
		}
	}
}

func move_players(array [3][3]string, simvol string) {
	x := 0
	k := 0
	sym := ""
	for !is_full(array) {
		sym = win(array)
		if sym == "x" || sym == "0" {
			break
		}
		qwe(array)
		fmt.Scan(&x)
		if x > 9 || x < 1 {
			fmt.Print("err")
		} else {
			for i := 0; i < 3; i++ {
				for j := 0; j < 3; j++ {
					k++
					if x == k {
						if array[i][j] == "_" {
							simvol = posledova(simvol)
							if simvol == "x" {
								array[i][j] = simvol
								k = 0
								i = 3
								break
							} else {
								array[i][j] = simvol
								k = 0
								i = 3
								break
							}
						} else {
							fmt.Println("Место занято")
						}
					}
				}
			}
		}
	}
	//sym := win(array)
	field(array)
	if sym == "x" || sym == "0" {
		fmt.Printf("\nWin %s", sym)
	} else {
		fmt.Print("\n", sym)
	}
}

// Последовательность ходов
func posledova(sim string) string {
	if sim == "x" {
		return "0"
	} else {
		return "x"
	}

}

// Отрисовка поля
func field(array [3][3]string) {
	for i := 0; i < 3; i++ {
		fmt.Print("\n")
		for j := 0; j < 3; j++ {
			fmt.Printf("%2s", array[i][j])
		}
	}
}

// Функция для оценки хода
func ocenka(array [3][3]string, sim string) int {
	sym := win(array)
	arrocenka := []int{}
	if sym == "x" {
		return -1
	}
	if sym == "0" {
		return 1
	}
	if sym == "Draft" {
		return 0
	}
	arrayfield := possibl_move(array, sim)
	for i := 0; i < len(arrayfield); i++ {
		k := ocenka(arrayfield[i], posledova(sim))
		arrocenka = append(arrocenka, k)
	}
	if sim == "x" {
		x := reduce(arrocenka, min)
		return x
	} else if sim == "0" {
		o := reduce(arrocenka, max)
		return o
	} else {
		return 0
	}
}

//x = -1(player), 0 = 1(computer),ничья = 0

// Лучший ход
func move(array [3][3]string, sym string) [3][3]string {
	arrayboard := possibl_move(array, sym)
	arraynum := []int{}
	for i := 0; i < len(arrayboard); i++ {
		num := ocenka(arrayboard[i], posledova(sym))
		arraynum = append(arraynum, num)
	}
	max := arraynum[0]
	array = arrayboard[0]

	for i := 1; i < len(arrayboard); i++ {
		if max < arraynum[i] {
			max = arraynum[i]
			array = arrayboard[i]
		}
	}
	return array
}
func play_comp(array [3][3]string, simvol string) {
	x := 0
	k := 0
	for !is_full(array) {
		sym := win(array)
		if sym == "x" || sym == "0" {
			break
		}
		qwe(array)
		simvol = posledova(simvol)
		if simvol == "x" {
			fmt.Scan(&x)
			k = 0
			for i := 0; i < 3; i++ {
				for j := 0; j < 3; j++ {
					k++
					if k == x {
						if array[i][j] == "_" {
							array[i][j] = simvol
							k = 0
							i = 3
							break
						}
					}
				}
			}
		}
		if simvol == "0" {
			array = move(array, simvol)
		}
	}
	sym := win(array)
	field(array)
	if sym == "x" || sym == "0" {
		fmt.Printf("\nWin %s", sym)
	} else {
		fmt.Print("\n", sym)
	}
}

// Поле с цифрами. Для удобства ходьбы.
func qwe(array [3][3]string) {
	k := "0"
	for j := 0; j < 3; j++ {
		fmt.Print("\n")
		for q := 0; q < 3; q++ {
			k = string(k[0] + 1)
			if array[j][q] == "_" {
				array[j][q] = k
				fmt.Printf("%2s", array[j][q])
			} else {
				fmt.Printf("%2s", array[j][q])
			}
		}
	}
	fmt.Println()
}

// computer = "0"
func main() {

	simvol := "0"
	//play := 0
	array := [3][3]string{
		{"_", "_", "_"},
		{"_", "_", "_"},
		{"_", "_", "_"},
	}
	//possibl_move(array, simvol)
	// fmt.Print("Игра против компьютера, нажмите 1\n", "Игра вдвоем, нажмите 2\n")
	// fmt.Scan(&play)
	// if play == 1 {
	// 	play_comp(array, simvol)
	// }
	// if play == 2 {
	move_players(array, simvol)

	// }
	//glubina := 0
	//number_possible_moves(array, simvol, glubina)
	//move_playersTwo(array, simvol)
}
