"Ride base class"
Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance |

    Ride class >> newWith: id pickup: pickup dropoff: dropoff distance: dist [
        | obj |
        obj := self new.
        obj initializeWith: id pickup: pickup dropoff: dropoff distance: dist.
        ^ obj
    ]

    Ride >> initializeWith: id pickup: pickup dropoff: dropoff distance: dist [
        rideID := id.
        pickupLocation := pickup.
        dropoffLocation := dropoff.
        distance := dist.
    ]

    Ride >> fare [
        self subclassResponsibility.
    ]

    Ride >> rideDetails [
        Transcript show: 'Ride ID: ', rideID; cr.
        Transcript show: 'Pickup: ', pickupLocation; cr.
        Transcript show: 'Dropoff: ', dropoffLocation; cr.
        Transcript show: 'Distance: ', distance printString, ' miles'; cr.
    ]
]

"StandardRide subclass"
Ride subclass: StandardRide [

    StandardRide >> fare [
        ^ distance * 2.0
    ]

    StandardRide >> rideDetails [
        Transcript show: 'Standard Ride'; cr.
        super rideDetails.
        Transcript show: 'Fare: $', (self fare) printString; cr.
    ]
]

"PremiumRide subclass"
Ride subclass: PremiumRide [

    PremiumRide >> fare [
        ^ distance * 3.5
    ]

    PremiumRide >> rideDetails [
        Transcript show: 'Premium Ride'; cr.
        super rideDetails.
        Transcript show: 'Fare: $', (self fare) printString; cr.
    ]
]

"Driver class"
Object subclass: Driver [
    | driverID name rating assignedRides |

    Driver class >> newWith: id name: n rating: r [
        | obj |
        obj := self new.
        obj initializeWith: id name: n rating: r.
        ^ obj
    ]

    Driver >> initializeWith: id name: n rating: r [
        driverID := id.
        name := n.
        rating := r.
        assignedRides := OrderedCollection new.
    ]

    Driver >> addRide: ride [
        assignedRides add: ride.
    ]

    Driver >> getDriverInfo [
        Transcript show: 'Driver ID: ', driverID, ', Name: ', name, ', Rating: ', (rating asFloat printString); cr.
        Transcript show: 'Assigned Rides: ', assignedRides size printString; cr.
        assignedRides do: [:ride | ride rideDetails. Transcript cr].
    ]
]

"Rider class"
Object subclass: Rider [
    | riderID name requestedRides |

    Rider class >> newWith: id name: n [
        | obj |
        obj := self new.
        obj initializeWith: id name: n.
        ^ obj
    ]

    Rider >> initializeWith: id name: n [
        riderID := id.
        name := n.
        requestedRides := OrderedCollection new.
    ]

    Rider >> requestRide: ride [
        requestedRides add: ride.
    ]

    Rider >> viewRides [
        Transcript show: 'Rider ID: ', riderID, ', Name: ', name; cr.
        Transcript show: 'Requested Rides: ', requestedRides size printString; cr.
        requestedRides do: [:ride | ride rideDetails. Transcript cr].
    ]
]

"Main test code"
| ride1 ride2 ride3 driver rider allRides |

ride1 := StandardRide newWith: 'R001' pickup: 'Downtown' dropoff: 'Airport' distance: 10.
ride2 := PremiumRide newWith: 'R002' pickup: 'Mall' dropoff: 'Hotel' distance: 5.
ride3 := StandardRide newWith: 'R003' pickup: 'Office' dropoff: 'Home' distance: 15.

driver := Driver newWith: 'D001' name: 'Alice' rating: 4.
driver addRide: ride1.
driver addRide: ride2.

rider := Rider newWith: 'P001' name: 'Bob'.
rider requestRide: ride1.
rider requestRide: ride3.

Transcript show: '--- All Ride Details (Polymorphism Demo) ---'; cr.
allRides := OrderedCollection with: ride1 with: ride2 with: ride3.
allRides do: [:ride | ride rideDetails. Transcript cr].

driver getDriverInfo.
rider viewRides.
