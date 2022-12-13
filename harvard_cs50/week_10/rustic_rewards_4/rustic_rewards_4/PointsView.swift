//
//  PointsView.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-03.
//

import SwiftUI

struct PointsView: View {
    @EnvironmentObject var dataManager: DataManager
    
    
    var body: some View {
        ZStack{
            Color.red.opacity(0.80)
            Text("Points Available: " + String(dataManager.pointCount - dataManager.redeemedCount))
                .frame(width: 300, height: 100)
                .foregroundColor(.white)
                .background{
                    RoundedRectangle(cornerRadius: 20, style: .continuous)
                        .fill(.linearGradient(colors: [.gray], startPoint: .top, endPoint: .bottomTrailing)).opacity(0.80)
                }
                .offset(y: 100)
                .aspectRatio(contentMode: .fit)
            
            Image(uiImage: UIImage(data: returnDate(str: USER_ID))!).resizable().frame(width: 250, height: 250)
                .padding()
                .offset(y: -100)
                .aspectRatio(contentMode: .fit)
        }
        .ignoresSafeArea()
    }
    func returnDate(str: String)->Data{
        let filter = CIFilter(name: "CIQRCodeGenerator")
        let data = str.data(using: .utf8, allowLossyConversion: false)
        filter?.setValue(data, forKey: "inputMessage")
        let image = filter?.outputImage?.transformed(by: CGAffineTransform(scaleX: 5, y: 5))
        let uiimage = UIImage(ciImage: image!)
        return uiimage.pngData()!
    }
}

struct PointsView_Previews: PreviewProvider {
    static var previews: some View {
        PointsView()
            .environmentObject(DataManager())
    }
}
