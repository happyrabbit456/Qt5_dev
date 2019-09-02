.pragma library

function func() {
    //    JS数字
    var x = 627;
    //    JS字符串
    var txt = "Hello word!";
    //    JS日期
    var myDate = new Date();
    //    JS数组
}

Qt.include("factorial.js")

function showCalculations(value) {
    console.log("Call factorial() from script.js:",
                factorial(value));
    var num =  Number(value);
    console.log("num:",num);
}
