function main()
    BeginPath();
    MoveTo(10, 10)
    LineTo(250, 950)
    LineTo(80, 650)
    Circle(300,300,150)
    ClosePath()
    
    color = ColorFromRGB(100,150,0)
    SetFillColor(color)
    Fill()
end
