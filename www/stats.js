
let tooltip = d3.select("body")
				.append("div")
				.attr("id", "tooltip");

function adjustTooltipPosition(event) {
	const tooltipWidth = tooltip.node().offsetWidth;
	const pageWidth = window.innerWidth;

	let left = event.clientX + 10;
	let top = event.clientY - 50;

	let renderLeft = event.pageX + 10;
	let renderTop = event.pageY - 50;

	if (left + tooltipWidth + 20 > pageWidth) {
		left = pageWidth - tooltipWidth - 10;
		renderLeft = event.pageX - tooltipWidth - 10;
	}

	tooltip.style("top", renderTop + "px")
			.style("left", renderLeft + "px");
}

function createChart(divId, svgId, data, YrangeX, YrangeY, YTrans, XrangeY, XTransX, YTransY, textTrans, decRect, h)
{
	let cont_div = d3.select(divId);
	let divWidth = cont_div.node().clientWidth;
	let divHeight = cont_div.node().clientHeight;

	let div_svg = d3.select(divId)
						.append("svg")
						.attr("id", svgId)
						.attr("viewBox", `0 0 ${divWidth} ${divHeight}`)
						.attr("preserveAspectRatio", "xMidYMid meet");

	const yScale = d3.scaleLinear()
					.domain([0, d3.max(data, (d) => d.students)])
					.range([divHeight - YrangeX, YrangeY]);
	const yAxis = d3.axisLeft(yScale);
	div_svg.append("g")
		.attr("transform", YTrans)
		.call(yAxis);

	const xScale = d3.scaleBand()
		.domain(data.map(d => d.name))
		.range([0, divWidth - XrangeY]);
	const xAxis = d3.axisBottom(xScale);
	div_svg.append("g")
		.attr("transform", "translate(" + XTransX +", " + (divHeight - YTransY) + ")")
		.call(xAxis)
		.selectAll("text")
		.attr("transform", (d, i) => textTrans)
		.style("text-anchor", "end");

	div_svg.selectAll("rect")
		.data(data)
		.enter()
		.append("rect")
		.attr("x", (d) => xScale(d.name) + decRect)
		.attr("y", (d) => yScale(d.students))
		.attr("width", xScale.bandwidth())
		.attr("height", (d) => divHeight - h - yScale(d.students))
		.attr("fill", "steelblue")
		.on("mouseover", function() {
			tooltip.style("visibility", "visible");
			d3.select(this).style("fill", "lightgray");
		})
		.on("mousemove", function(event, d) {
			tooltip.html(`${d.name}<br>${d.students}`);
			adjustTooltipPosition(event);
		})
		.on("mouseout", function() {
			d3.select(this).style("fill", "steelblue");
			tooltip.style("visibility", "hidden");
		});
}

let continents_div = d3.select("#continents-div");
let divWidth = continents_div.node().clientWidth;
let divHeight = continents_div.node().clientHeight;

let continents_svg = d3.select("#continents-div")
					.append("svg")
					.attr("id", "continents-svg")
					.attr("viewBox", `0 0 ${divWidth} ${divHeight}`)
					.attr("preserveAspectRatio", "xMidYMid meet");

fetch("./campus.json")
	.then(response => response.json())
	.then(data => {

		const contData = d3.rollups(data, v => d3.sum(v, (d) => d.students), (d) => d.continent)
							.map(([continent, students]) => ({ continent, students }));

		const yScale = d3.scaleLinear()
							.domain([0, d3.max(contData, (d) => d.students)])
							.range([divHeight - 30, 20]);
		const yAxis = d3.axisLeft(yScale);
		continents_svg.append("g")
			.attr("transform", "translate(45,0)")
			.call(yAxis);

		const xScale = d3.scaleBand()
						.domain(contData.map(d => d.continent))
						.range([0, divWidth - 45]);
		const xAxis = d3.axisBottom(xScale);
		continents_svg.append("g")
			.attr("transform", "translate(45, " + (divHeight - 30) + ")")
			.call(xAxis)
			.selectAll("text")
			.attr("transform", (d, i) => `translate(10, 5)`)
			.style("text-anchor", "end");

		continents_svg.selectAll("rect")
			.data(contData)
			.enter()
			.append("rect")
			.attr("x", (d) => xScale(d.continent) + 46)
			.attr("y", (d) => yScale(d.students))
			.attr("width", xScale.bandwidth())
			.attr("height", (d) => divHeight - 30 - yScale(d.students))
			.attr("fill", "steelblue")
			.on("mouseover", function() {
				tooltip.style("visibility", "visible");
				d3.select(this).style("fill", "lightgray");
			})
			.on("mousemove", function(event, d) {
				tooltip.html(`${d.continent}<br>${d.students}`)
					.style("top", (event.pageY - 10) + "px")
					.style("left", (event.pageX + 10) + "px");
			})
			.on("mouseout", function() {
				d3.select(this).style("fill", "steelblue");
				tooltip.style("visibility", "hidden");
			});
});

fetch("./campus.json")
	.then(response => response.json())
	.then(data => {

	const afData = data.filter(d => d.continent === "Africa");
	createChart("#africa-div", "africa-svg", afData, 20, 10, "translate(35, 0)", 40, 35, 20,  "translate(30, 0)", 35, 20);

	const amData = data.filter(d => d.continent === "America");
	createChart("#america-div", "america-svg", amData, 20, 10, "translate(40, 0)", 40, 40, 20,  "translate(30, 0)", 40, 20);

	const ocData = data.filter(d => d.continent === "Oceania");
	createChart("#oceania-div", "oceanie-svg", ocData, 20, 10, "translate(30, 0)", 40, 30, 20,  "translate(30, 0)", 30, 20);

	const euData = data.filter(d => d.continent === "Europe");
	createChart("#europe-div", "europe-svg", euData, 60, 5, "translate(30,0)", 40, 30, 60, "translate(0, 0) rotate(-45)", 30, 60);

	const asData = data.filter(d => d.continent === "Asia");
	createChart("#asia-div", "asia-svg", asData, 60, 5, "translate(35,0)", 40, 35, 60, "translate(0, 0) rotate(-35)", 35, 60);

	createChart("#campus-div", "campus-svg", data, 75, 15, "translate(50,0)", 60, 50, 75, "translate(0, 0) rotate(-45)", 50, 75);
});
