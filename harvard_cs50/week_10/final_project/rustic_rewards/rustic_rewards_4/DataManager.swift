//
//  DataManager.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-02.
//

// This is a DataManager Class which grabs all user pizza data

import SwiftUI
import Firebase

class DataManager: ObservableObject{
    @Published var pizzas: [Pizza] = []
    @Published var pointCount = 0
    @Published var redeemedCount = 0
    var id_count = 0
    
    // Fetch Pizzas when called
    init(){
        fetchPizzas()
    }
    // Grabbing all pizza transaction from database
    func fetchPizzas() {
        pizzas.removeAll()
        let db = Firestore.firestore()
        let ref = db.collection("User_Pizza_Data").whereField("email", isEqualTo: USER_ID)
        ref.getDocuments{ snapshot, error in
            guard error == nil else{
                print(error!.localizedDescription)
                return
            }
            // Adding pizza structs to pizza list
            if let snapshot = snapshot{
                for document in snapshot.documents {
                    let data = document.data()
                    
                    let id = self.id_count
                    let date = data["date"] as? String ?? ""
                    let email = data["email"] as? String ?? ""
                    let points = data["points"] as? Int ?? 0
                    let redeemed = data["redeemed"] as? Int ?? 0
                    self.id_count += 1
                    self.pointCount += (data["points"] as! Int)
                    self.redeemedCount += (data["redeemed"] as! Int)
                    
                    let pizza = Pizza(id: id, email: email, date: date, points: points, redeemed: redeemed)
                    self.pizzas.append(pizza)
                    
                }
            }
        }
    }
}
