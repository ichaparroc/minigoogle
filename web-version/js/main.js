var min = 99;
var max = 999999;
var polygonMode = false;
var pointMode = false;
var rangeSearchMode = false;
var knnSearchMode = false;
var pointArray = new Array();
var lineArray = new Array();
var activeLine;
var activeShape;
var canvas;
var poligonos = [];
var polyToRender = [];
var polCount = 0;
var rect1, isDown, origX, origY;//para el rectangulo
var RSxmin, RSymin, RSxmax, RSymax;
var knnIsCheck = document.getElementById("knn-search");
var colorFounded = "#2eb82e"
var MBR = [];

//------------------------------------------------------------
$(window).load(function(){
  prototypefabric.initCanvas();
  $('#create-polygon').click(function() {
    polygonMode = true;
    pointMode = false;
    rangeSearchMode = false;
    knnSearchMode = false;
    prototypefabric.polygon.drawPolygon();
    knnIsCheck.checked = false;
    showKNNOptions()
    RepaintCanvas(MBR);
  });
 $('#create-point').click(function() {
    polygonMode = false;
    pointMode = true;
    rangeSearchMode = false;
    knnSearchMode = false;
    prototypefabric.point.drawPoint();
    knnIsCheck.checked = false;
    showKNNOptions()
    RepaintCanvas(MBR);
  });
 $('#range-search').click(function() {
    polygonMode = false;
    pointMode = false;
    rangeSearchMode = true;
    knnSearchMode = false;
    knnIsCheck.checked = false;
    showKNNOptions()
    RepaintCanvas(MBR);
  });
  $('#knn-search').click(function(){
    polygonMode = false;
    pointMode = false;
    rangeSearchMode = false;
    knnSearchMode = true;
    RepaintCanvas(MBR);
  });
});

var prototypefabric = new function(){
  this.initCanvas = function () {
    canvas = window._canvas = new fabric.Canvas('c');
    canvas.setWidth(800);
    canvas.setHeight(600);
    //canvas.selection = false;

    canvas.on('mouse:down', function (options) {
      if(options.target && options.target.id == pointArray[0].id){
        prototypefabric.polygon.generatePolygon(pointArray);
        poligonos[polCount] = prototypefabric.polygon.polygonPoints;
        var minmaxPoints = minmax_pol(prototypefabric.polygon.polygonPoints)
        var toSend = {
          order: polCount,
          minP: [minmaxPoints[0][0], minmaxPoints[0][1]],
          maxP: [minmaxPoints[1][0], minmaxPoints[1][1]],
        }
        mqttPublish(local_clientMQTTPaho, "web/insert", toSend)
        prototypefabric.polygon.polygonPoints = [];
        prototypefabric.polygon.polygonLength = 0;
        polCount++;
      }
      if(polygonMode){
        prototypefabric.polygon.addPoint(options);
      }
      if(knnSearchMode && knnIsCheck.checked){
        var knn = document.getElementsByName("quantity")[0].value;
        var toSend = {
          x: parseInt(canvas.getPointer().x),
          y: parseInt(canvas.getPointer().y),
          k: parseInt(knn),
        }
        RepaintCanvas(MBR);
        if(poligonos.length >0){
          mqttPublish(local_clientMQTTPaho, "web/knn", toSend)
        }
      }
      if(pointMode){
        prototypefabric.point.addPoint(options);
        poligonos[polCount] = prototypefabric.point.points;
        var toSend = {
          order: polCount,
          minP: [prototypefabric.point.points[0], prototypefabric.point.points[1]],
          maxP: [prototypefabric.point.points[0], prototypefabric.point.points[1]],
        }
        mqttPublish(local_clientMQTTPaho, "web/insert", toSend)
        prototypefabric.point.points = [];
        polCount++;
      }
      if(rangeSearchMode){
        isDown = true;
        var pointer = canvas.getPointer(options.e);
        origX = pointer.x;
        origY = pointer.y;
        var pointer = canvas.getPointer(options.e);
        rect1 = new fabric.Rect({
          left: origX,
          top: origY,
          originX: 'left',
          originY: 'top',
          width: pointer.x-origX,
          height: pointer.y-origY,
          angle: 0,
          evented: false,
          fill: 'transparent',
          strokeWidth: 2,
          strokeDashArray: [10, 5],
          stroke: 'black',
        });
        canvas.add(rect1);
      }
    });

    canvas.on('mouse:up', function (options) {
      if(rangeSearchMode){
        isDown = false;
        RSxmin = parseInt(origX);
        RSymin = parseInt(origY);

        if(RSxmin > RSxmax){
          var temp = RSxmin
          RSxmin = RSxmax
          RSxmax = temp
        }
        if(RSymin > RSymax){
          var temp = RSymin
          RSymin = RSymax
          RSymax = temp
        }
        var toSend={
          minP:[RSxmin, RSymin],
          maxP:[RSxmax, RSymax],
        }
        if(poligonos.length >0){
          mqttPublish(local_clientMQTTPaho, "web/search", toSend)
        }
        rangeSearchMode = false;
      }
    });
    canvas.on('mouse:move', function (options) {
      if(rangeSearchMode){
        if (!isDown) return;
        var pointer = canvas.getPointer(options.e);
        if(origX>pointer.x){
          rect1.set({ left: Math.abs(pointer.x) });
        }
        if(origY>pointer.y){
          rect1.set({ top: Math.abs(pointer.y) });
        }
        rect1.set({ width: Math.abs(origX - pointer.x) });
        rect1.set({ height: Math.abs(origY - pointer.y) });
        canvas.renderAll();
        RSxmax = parseInt(pointer.x);
        RSymax = parseInt(pointer.y);
      }
      if(activeLine && activeLine.class == "line"){
        var pointer = canvas.getPointer(options.e);
        activeLine.set({ x2: pointer.x, y2: pointer.y });

        var points = activeShape.get("points");
        points[pointArray.length] = {
          x:pointer.x,
          y:pointer.y
        }
        activeShape.set({
          points: points
        });
        canvas.renderAll();
      }
      //------desactiva los  objetos para editarse-----
      canvas.deactivateAll();
      canvas.selection = false;
      canvas.forEachObject(function(o) {
      o.selectable = false;
       });
     //-------------------------------------------------
      canvas.renderAll();
    });
  };
};

  var set0 = ['First result','Second result','Third result'];
  var set1 = ['First text','Second text','Third text'];
     function get_list(array) {
       // Create the list element:
       var list = document.createElement('ul');
       list.className="collection with-header";


       for (var i = 0; i < array.length; i++) {
         // Create the list item:
         var item = document.createElement('li');
         item.className="collection-item";
         // Set its contents:
         item.appendChild(document.createTextNode(array[i]));
         item.setAttribute("id", i);
         item.addEventListener("click", visualize_result,false);
         // Add it to the list:
         list.appendChild(item);
         }
         // Finally, return the constructed list:
         return list;
}
// Add the contents of options[0] to #foo:

function visualize_list(){
document.getElementById('search_list').innerHTML = "";
var h = document.createElement("H5");
var text1="Resultados de búsqueda ";
var t = document.createTextNode(text1+document.getElementById("query").value+":");
h.appendChild(t);
document.getElementById('search_list').appendChild(h);
document.getElementById('search_list').appendChild(get_list(set0));



}
/*
function visualize_list(){
console.log(document.getElementById('search_list'));
alert("blavla");
}
*/
function visualize_result(){
document.getElementById('text_result').innerHTML = "";
document.getElementById('text_result').innerHTML = set1[this.id];
}
