//
//  rustic_adminApp.swift
//  rustic_admin
//
//  Created by Richard Andison on 2022-12-05.
//

import SwiftUI
import Firebase

@main
struct rustic_adminApp: App {
    
    init(){
        FirebaseApp.configure()
    }
    
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}
