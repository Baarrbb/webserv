const continents = ["All", "Europe", "Africa", "Asia", "America", "Oceania"];

// let div = d3.select("body")
// 			.append("div")
// 			.attr("id", "map");
let div = d3.select("#map");

let icon = L.icon({
	iconUrl: './images//mark_42.png',
	iconSize: [44, 46],
	iconAnchor: [22,46],
	popupAnchor: [0, -46]
});

let map = L.map('map', { minZoom: 2 })
			.setView([48.861325, 2.34195], 2);

L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
	attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
}).addTo(map);


let allCluster = L.markerClusterGroup({ showCoverageOnHover: false });
let europeCluster = L.markerClusterGroup({ showCoverageOnHover: false });
let africaCluster = L.markerClusterGroup({ showCoverageOnHover: false });
let asiaCluster = L.markerClusterGroup({ showCoverageOnHover: false });
let americaCluster = L.markerClusterGroup({ showCoverageOnHover: false });
let oceaniaCluster = L.markerClusterGroup({ showCoverageOnHover: false });

let allMarkers = [];
let europeMarkers = [];
let africaMarkers = [];
let asiaMarkers = [];
let americaMarkers = [];
let oceaniaMarkers = [];

let radioControl = L.control({ position: 'topright' });
radioControl.onAdd = function(map) {
	let div = L.DomUtil.create('div', 'radio-controls');
	div.innerHTML = continents.map(continent =>
		`<label>
			<input type="radio" name="continent" value="${continent}" ${continent === "All" ? "checked" : ""}>
			${continent}
		</label>`).join('<br>');
		return div;
};

radioControl.addTo(map);

fetch("./campus.json")
		.then(response => response.json())
		.then(data => {
			data.forEach(campus => {
				let marker = L.marker([campus.lat, campus.lon], {icon: icon})
					.bindPopup(campus.name)
					.on('click', function() {
						map.setView([campus.lat, campus.lon], 10);
					});
				
				switch (campus.continent) {
					case 'Europe':
						europeMarkers.push(marker);
						europeCluster.addLayer(marker);
						break;
					case 'Africa':
						africaMarkers.push(marker);
						africaCluster.addLayer(marker);
						break;
					case 'Asia':
						asiaMarkers.push(marker);
						asiaCluster.addLayer(marker);
						break;
					case 'America':
						americaMarkers.push(marker);
						americaCluster.addLayer(marker);
						break;
					case 'Oceania':
						oceaniaMarkers.push(marker);
						oceaniaCluster.addLayer(marker);
						break;
				}
				allMarkers.push(marker);
				allCluster.addLayer(marker);
			});
			map.addLayer(allCluster);
})

map.on('moveend', function() {
	markers.refreshClusters();
});

function switchClusterLayer(newCluster, markers) {
	map.eachLayer(layer => {
		if (layer instanceof L.MarkerClusterGroup) {
			layer.clearLayers();
			map.removeLayer(layer);
		}
	});
	if (newCluster) {
		markers.forEach(marker => newCluster.addLayer(marker));
		map.addLayer(newCluster);
		map.fitBounds(newCluster.getBounds());
	}
}

document.querySelectorAll('input[name="continent"]')
	.forEach(radio => 
		radio.addEventListener('change', function() {
			switch (this.value) {
				case 'All':
					switchClusterLayer(allCluster, allMarkers);
					break;
				case 'Europe':
					switchClusterLayer(europeCluster, europeMarkers);
					break;
				case 'Africa':
					switchClusterLayer(africaCluster, africaMarkers);
					break;
				case 'Asia':
					switchClusterLayer(asiaCluster, asiaMarkers);
					break;
				case 'America':
					switchClusterLayer(americaCluster, americaMarkers);
					break;
				case 'Oceania':
					switchClusterLayer(oceaniaCluster, oceaniaMarkers);
					break;
			}
		})
	);
