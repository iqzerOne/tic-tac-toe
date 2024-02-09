function max(x,y){
    if (x < y) {
        x = y
    }
    return x
}

function min(x,y){
    if (x > y){
        x = y
    }
    return x
}
//Нахождение минимального и максимального числа
function reduce(array,f) {
    let num = array[0]
    for (let i = 1; i < array.length; i++){
        num = f(num,array[i])
    }
    return num
}
//Счетчки символа на линию
function win_count_line(array, sim, line) {
    let win = 0
    for(let i = 0; i < 3; i++) {
        if (array[line][i] == sim) {
            win += 1
        }else{
            break
        }
    }
    return win
}
//Счетчки символа на столбик
function win_count_column(array, sim, column) {
    let win = 0
    for(let i = 0; i < 3; i++) {
        if (array[i][column] == sim) {
            win += 1
        } else {
            break
        }
    }
    return win
}
// Првоерка на победу
function win(array){
    let win = 0
    for (let i = 0;i < 3;i++) {
            win = win_count_line(array,array[i][0],i)
            if (win == 3){
                if (array[i][0] == "x"){
                    return "x"
                }
                if (array[i][0] == "0"){
                    return "0"
                }
            }
    }

    for (let i = 0;i < 3;i++) {
        win = win_count_column(array,array[0][i],i)
        if (win == 3){
            if (array[0][i] == "x"){
                return "x"
            }
            if (array[0][i] == "0"){
                return "0"
            }
        }
    }

    if ((array[0][0] == array[1][1]&& array[2][2] == array[1][1]) || (array[0][2] == array [1][1] && array[1][1] == array[2][0])){
        if (array[1][1] == "x"){
            return "x"
        }
        if (array[1][1] == "0"){
            return "0"
        }
    }
    while(!is_full(array)){
        return "continue"
    }
    return "Draft"
}
//Проверка на заполненность 
function is_full(array) {
    for (let i = 0;i < 3; i++) {
        for (let j = 0;j < 3; j++) {
            if (array[i][j] == "_") {
                return false
            }
        }
    }
    return true
}
//Смена символов
function change(sim) {
    if (sim == "x") {
        return "0"
    } else {
        return "x"
    }
}
//Печать полей на экран
function debug(array) {
    for (let i = 0; i < 3; i++) {
        console.log()
        for (let j = 0; j < array.length; j++) {
            if (j != 0) {
                process.stdout.write("|")
            }
            for (let k = 0; k < 3; k++) {
                process.stdout.write(array[j][i][k])
            }
        }
    }
}
//Клонирование массива
function clone (src) {
    return JSON.parse(JSON.stringify(src));
}
//Возможные ходы
function possible_move(array, sim) {
    let pos = []
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            if (array[i][j] == "_") {
                let newar = clone(array)
                newar[i][j] = sim
                pos.push(newar)
            }
        }
    }
    return pos
}
//Поле
function field(array) {
    for (let i = 0; i < 3; i++) {
        console.log()
        for (let j = 0; j < 3; j++) {
            process.stdout.write(array[i][j])
            process.stdout.write(" ")
        }
    }
}
// Поле с цифрами
 function number_field(array) {
    let k = "0"
    for (let i = 0; i < 3; i++) {
        console.log()
        for (let j = 0; j < 3; j++) {
            k = k.charCodeAt([0]) + 1
            k = String.fromCharCode(k)
            if (array[i][j] == "_") {
                let copyarray = clone(array)
                copyarray[i][j] = k
                process.stdout.write(copyarray[i][j])
                process.stdout.write(" ")
                    
            } else {
                process.stdout.write(array[i][j])
                process.stdout.write(" ")
                    
            }
        }
    }
}
//Оценка хода
function ocenka(array,simvol) {
    let winn = win(array)
    let arrayocenka = []
    if (winn == "x"){
        return -1
    }
    if (winn == "0"){
        return 1
    }
    if (winn == "Draft"){
        return 0
    }
    let arrayfield = possible_move(array,simvol)
    for (let i = 0; i < arrayfield.length;i++){
        let k = ocenka(arrayfield[i],change(simvol))
        arrayocenka.push(k)
    }
    if (simvol == "x") {
		let x = reduce(arrayocenka, min)
		return x
	} else if (simvol == "0") {
		let o = reduce(arrayocenka, max)
		return o
	} else {
		return 0
	}
}
//Лучший ход
function move(array,simvol) {
    let arrayboard = possible_move(array,simvol)
    let arraynum = []
    for(let i = 0;i < arrayboard.length; i++) {
        let num = ocenka(arrayboard[i],change(simvol))
        arraynum.push(num)
    }
    let max = arraynum[0]
    array = arrayboard[0]
    for (let i = 1; i < arrayboard.length; i++) {
		if (max < arraynum[i]) {
			max = arraynum[i]
			array = arrayboard[i]
		}
	}
	return array
}

//Игра с компьютером 
function play_comp(array,simvol) {
let x = 0
let k = 0
const readline = require('readline-sync')
    while(!is_full(array)) {
        let is_win = win(array)
        if (is_win == "x"|| is_win == "0"){
            break
        }
        number_field(array)
        console.log()
        simvol = change(simvol)
        if (simvol == "x") {
            x = readline.question()
			k = 0
			for (let i = 0; i < 3; i++) {
				for (let j = 0; j < 3; j++) {
					k++
					if (k == x) {
						if (array[i][j] == "_") {
							array[i][j] = simvol
							k = 0
							i = 3
							break
						}
					}
				}
			}
        }
        if (simvol == "0") {
			array = move(array, simvol)
		}
    }
    let sym = win(array)
	field(array)
	if (sym == "x" || sym == "0") {
		console.log("\nWin %s", sym)
	} else {
		console.log("\n", sym)
	}
}

function players(array,simvol) {
    let x, k = 0
    const readline = require('readline-sync')
    while(!is_full(array)) {
        let sym = win(array)
		if (sym == "x" || sym == "0") {
			break
		}
		number_field(array)
		x = readline.question()
		if (x > 9 || x < 1) {
			console.log("err")
		} else {
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
					k++
					if (x == k) {
						if (array[i][j] == "_") {
							simvol = change(simvol)
							if (simvol == "x") {
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
							console.log("Место занято")
						}
					}
				}
			}
		}
	}
	let sym = win(array)
	field(array)
	if (sym == "x" || sym == "0") {
		console.log("\nWin %s", sym)
	} else {
		console.log("\n", sym)
	}
}


let simvol = "0"
let pole = [
    ["_", "_", "_"],
    ["_", "_", "_"],
    ["_", "_", "_"],
]
//play_comp(pole,simvol)
players(pole,simvol)
//console.log(win(pole))
