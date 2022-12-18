//
//  DataManager.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-02.
//

import SwiftUI
import Firebase
import Foundation


class DataManager: ObservableObject{
    
    @Published var available_points = 0
    @Published var pointCount = 0
    @Published var redeemedCount = 0
    
    // Grabs available, total points earned, and total points redeemed
    func fetchPoints(email: String){
        self.available_points = 0
        self.pointCount = 0
        self.redeemedCount = 0
        let db = Firestore.firestore()
        let ref = db.collection("User_Pizza_Data").whereField("email", isEqualTo: email)
        
        // Getting all users point values
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
            
            let date_format = Date()
            let dateFormatter = DateFormatter()
            dateFormatter.dateFormat = "YY/MM/dd"
            let date = dateFormatter.string(from: date_format)
            
            
            
            ref.setData(["email": email, "points": pizzas, "date": date, "redeemed": 0])
            { err in
                if let err = err {
                    print("Error writing document: \(err)")
                } else {
                    print("Document successfully written!")
                }

            }
            
        }
        
        func redeemPoints(email: String, pizzas: Int){
            let date_format = Date()
            let dateFormatter = DateFormatter()
            dateFormatter.dateFormat = "YY/MM/dd"
            let date = dateFormatter.string(from: date_format)
            
            let db = Firestore.firestore()
            let ref = db.collection("User_Pizza_Data").document()
            if (available_points - (pizzas * 10)) < 0{
                return
            }
            else{
                ref.setData(["email": email, "points": 0, "date": date, "redeemed": (pizzas * 10)])
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

