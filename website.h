/*
    Tạo biến lưu trang web
*/
const char MainPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>BẢNG ĐIỀU KHIỂN</title>
    <style>
        * {
            margin: 0px;
        }

        .content {
            width: auto;
            height: auto;
            display: grid;
            grid-template-rows: auto auto auto auto;
            padding: 3%;
        }

        button {
            width: 50px;
            height: 50px;
        }

        .light {
            display: grid;
            grid-template-rows: auto auto auto auto auto;
            text-align: center;
            padding: 2%;
            grid-gap: 2%;
            height: 270px;
        }

        .fan {
            display: grid;
            grid-template-rows: auto auto auto;
            text-align: center;
            padding: 2%;
            grid-gap: 1%;
        }

        .label {
            padding: 20px 0;
            width: 100%;
            height: 30px;
            text-align: center;
            background-color: rgb(10, 179, 10);
            color: white;
            font-size: 150%;
            box-shadow: 0 0 20px rgba(0, 0, 0, 0.3)
        }

        .sensor,
        .light {
            border-bottom: 1px solid rgb(192, 191, 191);
        }

        .obser_sensor {
            display: grid;
            grid-template-columns: 30% auto 30%;
        }

        img {
            height: 60px;
            width: 60px;
        }

        .value {
            margin: auto;
        }

        #temp_v, #humi_v {
            font-size: 25px;
        }
        #temp_v {
            color: rgb(216, 0, 0);
        }
        #humi_v {
            color: rgb(0, 0, 199);
        }

        button {
            outline: none;
            border-radius: 50px;
            background-color: white;
            border: 1px solid green;
            cursor: pointer;
        }

        .btn_timer {
            width: 100px;
            height: 30px;
            border-radius: 10px;
        }

        .light select {
            width: 70px;
            height: 25px;
            outline: none;
            border: none;
            border-bottom: 2px solid rgb(7, 190, 7);
            cursor: pointer;
        }

        @media only screen and (min-width: 960px) {
            .container {
                width: 50%;
                height: auto;
                margin: auto;
                border-left: 1px solid rgb(207, 207, 207);
                border-bottom-left-radius: 10px;
                border-bottom-right-radius: 10px;
                box-shadow: 0 0 20px rgba(0, 0, 0, 0.3);
            }
        }
    </style>
</head>

<body>
    <div class="container">
        <div class="label">
            <p>BẢNG ĐIỀU KHIỂN</p>
        </div>
        <div class="content">
            <div class="sensor">
                <div class="obser_sensor">
                    <img src="https://img.icons8.com/color-glass/96/000000/temperature.png" />
                    <div class="value">
                        <p id="temp_v"></p>
                    </div>
                </div>
                <div class="obser_sensor">
                    <img src="https://img.icons8.com/color/96/000000/hygrometer.png" />
                    <div class="value">
                        <p id="humi_v"></p>
                    </div>
                </div>
            </div>
            <div class="light">
                <div>
                    <img src="https://img.icons8.com/officel/80/000000/light-on.png" />
                </div>
                <div>
                    <button id="Light" class="btn_light" onclick="_request('light')">BẬT</button>
                </div>
                <div id="start-time">
                    <select name="hour" id="hour-start">
                        <option value="none">None</option>
                    </select>
                    <label> : </label>
                    <select name="min" id="min-start">
                        <option value="none">None</option>
                    </select>
                    <label> : </label>
                    <select name="sec" id="sec-start">
                        <option value="none">None</option>
                    </select>
                </div>
                <div id="stop-time">
                    <select name="hour" id="hour-stop">
                        <option value="none">None</option>
                    </select>
                    <label> : </label>
                    <select name="min" id="min-stop">
                        <option value="none">None</option>
                    </select>
                    <label> : </label>
                    <select name="sec" id="sec-stop">
                        <option value="none">None</option>
                    </select>
                </div>
                <div class="alarm">
                    <button id="timer" class="btn_timer" onclick="_request('setTimer')">Hẹn giờ</button>
                </div>
            </div>

            <div class="fan">
                <div>
                    <img src="https://img.icons8.com/color/96/000000/fan.png" />

                </div>

                <div>
                    <button id="Fan" class="btn_fan" onclick="_request('offSpeed')">TẮT</button>
                </div>

                <div class="btn-group speed_fan">
                    <button id="Fan1" class="btn btn-outline-primary on_off" onclick="_request('speed_1')">1</button>
                    <button id="Fan2" class="btn btn-outline-primary on_off" onclick="_request('speed_2')">2</button>
                    <button id="Fan3" class="btn btn-outline-primary on_off " onclick="_request('speed_3')">3</button>
                </div>

            </div>
        </div>
    </div>

    <script>
        for (var i = 0; i <= 24; i++) {
            var h1 = document.createElement("OPTION");
            var h2 = document.createElement("OPTION");
            var x = i;
            if (i < 10) x = "0" + i;
            h1.setAttribute("value", x);
            h2.setAttribute("value", x);
            h1.innerHTML = i;
            h2.innerHTML = i;
            document.getElementById("hour-start").appendChild(h1);
            document.getElementById("hour-stop").appendChild(h2);
        }
        for (var i = 0; i <= 60; i++) {
            var m1 = document.createElement("OPTION");
            var s1 = document.createElement("OPTION");
            var m2 = document.createElement("OPTION");
            var s2 = document.createElement("OPTION");
            var x = i;
            if (i < 10) x = "0" + i;
            m1.setAttribute("value", x);
            s1.setAttribute("value", x);
            m1.innerHTML = i;
            s1.innerHTML = i;
            m2.setAttribute("value", x);
            s2.setAttribute("value", x);
            m2.innerHTML = i;
            s2.innerHTML = i;
            document.getElementById("min-start").appendChild(m1);
            document.getElementById("sec-start").appendChild(s1);
            document.getElementById("min-stop").appendChild(m2);
            document.getElementById("sec-stop").appendChild(s2);
        }

        var xhttp = new XMLHttpRequest();

        var data = "";
        function check_TimeSelect() {
            var start_time = document.getElementById("start-time").children;
            var stop_time = document.getElementById("stop-time").children;
            if (start_time[0].value != "none" && start_time[2].value != "none" && start_time[4].value != "none") {
                data += "start_time=" + start_time[0].value + ":" + start_time[2].value + ":" + start_time[4].value + "&";
            }
            else data += "start_time=none&";

            if (stop_time[0].value != "none" && stop_time[2].value != "none" && stop_time[4].value != "none") {
                data += "stop_time=" + stop_time[0].value + ":" + stop_time[2].value + ":" + stop_time[4].value;
            }
            else data += "stop_time=none";
        }
        
        function _request(url) {
            if (url == "setTimer") {
                check_TimeSelect();
                xhttp.open("POST", "/" + url, true);
                xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
                xhttp.send(data);
                data = "";
            }
            else {
                xhttp.open("POST", "/" + url, true);
                xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
                xhttp.send();
            }
        }

        function updateData() {
            if (xhttp.readyState == 4 && xhttp.status == 200) {
                var dataJson = JSON.parse(xhttp.responseText);
                console.log(dataJson);
                var temp = document.getElementById("temp_v");
                var humi = document.getElementById("humi_v");
                var light = document.getElementById("Light");
                var timer = document.getElementById("timer");
                var fanOff = document.getElementById("Fan");
                var speed1 = document.getElementById("Fan1");
                var speed2 = document.getElementById("Fan2");
                var speed3 = document.getElementById("Fan3");

                if(dataJson.Temp == "ERR") temp.innerHTML = "Không đo được nhiệt độ !";
                else temp.innerHTML = dataJson.Temp + "&#8451";
                if(dataJson.Humi == "ERR") humi.innerHTML = "Không đo được độ ẩm !";
                else humi.innerHTML = dataJson.Humi + "% RH";

                if (dataJson.Light == "ON") {
                    light.innerHTML = "TẮT";
                    light.style.backgroundColor = "rgb(10, 197, 10)";
                }
                else {
                    light.innerHTML = "BẬT";
                    light.style.backgroundColor = "white";
                }

                if(dataJson.Timer == "ON") {
                    timer.innerHTML = "Tắt hẹn giờ";
                    timer.style.backgroundColor = "rgb(10, 197, 10)";
                }
                else {
                    timer.innerHTML = "Hẹn giờ";
                    timer.style.backgroundColor = "white";
                }

                if (dataJson.Speed == "OFF") {
                    fanOff.style.backgroundColor = "rgb(10, 197, 10)";
                    speed1.style.backgroundColor = "white";
                    speed2.style.backgroundColor = "white";
                    speed3.style.backgroundColor = "white";
                }
                else {
                    if (dataJson.Speed == "1") {
                        fanOff.style.backgroundColor = "white";
                        speed1.style.backgroundColor = "rgb(10, 197, 10)";
                        speed2.style.backgroundColor = "white";
                        speed3.style.backgroundColor = "white";
                    }
                    else if (dataJson.Speed == "2") {
                        fanOff.style.backgroundColor = "white";
                        speed1.style.backgroundColor = "white";
                        speed2.style.backgroundColor = "rgb(10, 197, 10)";
                        speed3.style.backgroundColor = "white";
                    }
                    else {
                        fanOff.style.backgroundColor = "white";
                        speed1.style.backgroundColor = "white";
                        speed2.style.backgroundColor = "white";
                        speed3.style.backgroundColor = "rgb(10, 197, 10)";
                    }
                }
            }
        }

        function sync() {
            xhttp.open("GET", "/updateData", true);
            xhttp.onreadystatechange = updateData;
            xhttp.send();
        }

        setInterval(sync, 1000);
    </script>
</body>

</html>
)=====";
