//
//  DataManager.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-02.
//

import SwiftUI
import Firebase

class DataManager: ObservableObject{
    @Published var pizzas: [Pizza] = []
    @Published var pointCount = 0
    @Published var redeemedCount = 0
    init(){
        fetchPizzas()
    }
    
    func fetchPizzas() {
        pizzas.removeAll()
        let db = Firestore.firestore()
        let ref = db.collection("User_Pizza_Data").whereField("email", isEqualTo: USER_ID)
        ref.getDocuments{ snapshot, error in
            guard error == nil else{
                print(error!.localizedDescription)
                return
            }
            if let snapshot = snapshot{
                for document in snapshot.documents {
                    let data = document.data()
                    
                    let id = data["id"] as? Int ?? 0
                    let date = data["date"] as? String ?? ""
                    let email = data["email"] as? String ?? ""
                    let points = data["points"] as? Int ?? 0
                    self.pointCount += (data["points"] as! Int)
                    let redeemed = data["redeemed"] as? Int ?? 0
                    self.redeemedCount += (data["redeemed"] as! Int)
                    
                    let pizza = Pizza(id: id, email: email, date: date, points: points, redeemed: redeemed)
                    self.pizzas.append(pizza)
                    
                }
            }
        }
    }
}
