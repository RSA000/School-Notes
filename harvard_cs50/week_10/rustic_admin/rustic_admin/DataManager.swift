//
//  DataManager.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-02.
//

import SwiftUI
import Firebase


class DataManager: ObservableObject{
    
    @Published var available_points = 0
    @Published var pointCount = 0
    @Published var redeemedCount = 0
    
    
    func fetchPoints(email: String){
        self.available_points = 0
        self.pointCount = 0
        self.redeemedCount = 0
        let db = Firestore.firestore()
        let ref = db.collection("User_Pizza_Data").whereField("email", isEqualTo: email)
        
        ref.getDocuments{ snapshot, error in
            guard error == nil else{
                print(error!.localizedDescription)
                return
            }
            
            if let snapshot = snapshot{
                for document in snapshot.documents {
                    let data = document.data()
                    
                    self.pointCount += (data["points"] as! Int)
                    self.redeemedCount += (data["redeemed"] as! Int)
                }
            }
            self.available_points = (self.pointCount - self.redeemedCount)
        }
    }
    
    
        func addPoints(email: String, pizzas: Int){
            
            let db = Firestore.firestore()
            let ref = db.collection("User_Pizza_Data").document()
            
            ref.setData(["email": email, "points": pizzas, "date": Date(), "redeemed": 0])
            { err in
                if let err = err {
                    print("Error writing document: \(err)")
                } else {
                    print("Document successfully written!")
                }

            }
            
        }
        
        func redeemPoints(email: String, pizzas: Int){
            
            let db = Firestore.firestore()
            let ref = db.collection("User_Pizza_Data").document()
            if available_points - (pizzas * 10) < 0{
                print(pointCount, redeemedCount, available_points)
                print("not enough points :(")
                
            }
            else{
                print(pointCount, redeemedCount, available_points)
                ref.setData(["email": email, "points": 0, "date": Date(), "redeemed": (pizzas * 10)])
                { err in
                    if let err = err {
                        print("Error writing document: \(err)")
                    } else {
                        print("Document successfully written!")
                    }
                }
            }
        }
    
    }

